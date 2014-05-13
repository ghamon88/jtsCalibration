#include "JTSCalibrationModule.h"
#include "JTScalibrationThread.h"

#include <cstdio>
#include <string>

using namespace yarp::os;
using namespace yarp::sig;
using namespace std;

/* 
 * Configure method. Receive a previously initialized
 * resource finder object. Use it to configure your module.
 * If you are migrating from the old Module, this is the 
 * equivalent of the "open" method.
 */

/*namespace JTSCalibration {
    JTSCalibrationModule::JTSCalibrationModule()
    {
        
    }*/

bool JTSCalibrationModule::configure(yarp::os::ResourceFinder &rf) {    

	_moduleName=rf.check("name",Value("JTSCalibration"),"Module Name").asString();
   	
	_robotName=rf.check("name",Value("iCub"),"Robot Name").asString();

	_period=rf.check("period",Value("10"),"Period in milliseconds").asInt();

        Bottle *initMsg;
	_gainRA=(double*)malloc(3*sizeof(double));
	_gainLA=(double*)malloc(3*sizeof(double));
	_gainRL=(double*)malloc(3*sizeof(double));
	_gainLL=(double*)malloc(3*sizeof(double));
	_offsetRA=(double*)malloc(3*sizeof(double));
	_offsetLA=(double*)malloc(3*sizeof(double));
	_offsetRL=(double*)malloc(3*sizeof(double));
	_offsetLL=(double*)malloc(3*sizeof(double));

	initMsg=rf.check("GainRA",Value("(2.52 0.0 3.53)"),"Gain Right Arm JTS").asList();
	for(int i=0; i<initMsg->size();i++){
		_gainRA[i]=initMsg->get(i).asDouble();
	}
	
	initMsg=rf.check("GainLA",Value("(0.0 0.0 0.0)"),"Gain Left Arm JTS").asList();
	for(int i=0; i<initMsg->size();i++){
		_gainLA[i]=initMsg->get(i).asDouble();
	}

	initMsg=rf.check("GainRL",Value("(0.0 0.0 0.0)"),"Gain Right Leg JTS").asList();
	for(int i=0; i<initMsg->size();i++){
		_gainRL[i]=initMsg->get(i).asDouble();
	}

	initMsg=rf.check("GainLL",Value("(0.0 0.0 0.0)"),"Gain Left Leg JTS").asList();
	for(int i=0; i<initMsg->size();i++){
		_gainLL[i]=initMsg->get(i).asDouble();
	}

	initMsg=rf.check("OffsetRA",Value("(2.52 0.0 3.53)"),"Offset Right Arm JTS").asList();
	for(int i=0; i<initMsg->size();i++){
		_offsetRA[i]=initMsg->get(i).asDouble();
	}
	
	initMsg=rf.check("OffsetLA",Value("(0.0 0.0 0.0)"),"Offset Left Arm JTS").asList();
	for(int i=0; i<initMsg->size();i++){
		_offsetLA[i]=initMsg->get(i).asDouble();
	}

	initMsg=rf.check("OffsetRL",Value("(0.0 0.0 0.0)"),"Offset Right Leg JTS").asList();
	for(int i=0; i<initMsg->size();i++){
		_offsetRL[i]=initMsg->get(i).asDouble();
	}

	initMsg=rf.check("OffsetLL",Value("(0.0 0.0 0.0)"),"Offset Left Leg JTS").asList();
	for(int i=0; i<initMsg->size();i++){
		_offsetLL[i]=initMsg->get(i).asDouble();
	}
	
	inputPortName_RA      = "/";
    	inputPortName_RA      += getName(
                           rf.check("InputPortRightArm", 
                           Value("right_arm/raw:i"),
                           "Input raw value right arm JTS port (string)").asString()
                           );
	inputPortName_LA      = "/";
    	inputPortName_LA      += getName(
                           rf.check("InputPortLeftArm", 
                           Value("left_arm/raw:i"),
                           "Input raw value left arm JTS port (string)").asString()
                           );

	inputPortName_RL      = "/";
    	inputPortName_RL      += getName(
                           rf.check("InputPortRightLeg", 
                           Value("right_leg/raw:i"),
                           "Input raw value right leg JTS port (string)").asString()
                           );
	inputPortName_LL      = "/";
    	inputPortName_LL      += getName(
                           rf.check("InputPortLeftLeg", 
                           Value("left_leg/raw:i"),
                           "Input raw value left leg JTS port (string)").asString()
                           );

    	outputPortName_RA        = "/";
    	outputPortName_RA       += getName(
                           rf.check("OutputPortRightArm", 
                           Value("right_arm/calibrated:o"),
                           "Output calibrated value right arm JTS port (string)").asString()
                           );

	outputPortName_LA        = "/";
    	outputPortName_LA       += getName(
                           rf.check("OutputPortLeftArm", 
                           Value("left_arm/calibrated:o"),
                           "Output calibrated value left arm JTS port (string)").asString()
                           );

	outputPortName_RL        = "/";
    	outputPortName_RL       += getName(
                           rf.check("OutputPortRightLeg", 
                           Value("right_leg/calibrated:o"),
                           "Output calibrated value right leg JTS port (string)").asString()
                           );

	outputPortName_LL        = "/";
    	outputPortName_LL       += getName(
                           rf.check("OutputPortLeftLeg", 
                           Value("left_leg/calibrated:o"),
                           "Output calibrated value left leg JTS port (string)").asString()
                           );


	

    	setName(_moduleName.c_str());

    	//initMsg.clear();
	
	/*
    	* attach a port of the same name as the module (prefixed with a /) to the module
    	* so that messages received from the port are redirected to the respond method
    	*/
    	handlerPortName =  "/";
    	handlerPortName += getName();         // use getName() rather than a literal 

    	if (!handlerPort.open(handlerPortName.c_str())) {           
        	cout << getName() << ": Unable to open port " << handlerPortName << endl;  
        return false;
    	}

    	attach(handlerPort);                  // attach to port


	//--------------------------CONTROL THREAD--------------------------
        _jtscalibrationThread = new JTSCalibrationThread(_moduleName,_robotName,_period,
						inputPortName_RA,inputPortName_LA,inputPortName_RL,inputPortName_LL,
						outputPortName_RA,outputPortName_LA,outputPortName_RL,outputPortName_LL,
                                                _gainRA,_gainLA,_gainRL,_gainLL,
						_offsetRA,_offsetLA,_offsetRL,_offsetLL);
        if (!_jtscalibrationThread || !_jtscalibrationThread->start()) {
          //  error_out("Error while initializing control thread. Closing module.\n");
            return false;
        }
        //_controlThread->setInitialConditions(_initialPiHat, _initialXi1);
        
        //info_out("JTS Calibration module correctly initialized\n");
        return true;
}
    

bool JTSCalibrationModule::interruptModule() {
	if(_jtscalibrationThread) _jtscalibrationThread->stop();
    	handlerPort.interrupt();
    	return true;
}

bool JTSCalibrationModule::close() {

    /* stop the thread */
	if(_jtscalibrationThread){
        	_jtscalibrationThread->stop();
		delete _jtscalibrationThread;
        	_jtscalibrationThread = NULL;
	}

	//closing ports de communication avec le module (commandes), pour le thread le faire dans thread-->release
	handlerPort.close();
	//info_out("about to close\n");
    	return true;
}

bool JTSCalibrationModule::respond(const Bottle& command, Bottle& reply) {
  string helpMessage =  string(getName().c_str()) + 
                        " commands are: \n" +  
                        "help \n" + 
                        "quit \n" + 
                        "bias ... set the JTS current values as offsets  \n";

  reply.clear(); 

  if (command.get(0).asString()=="quit") {
       reply.addString("quitting");
       return false;     
   }
   else if (command.get(0).asString()=="help") {
      cout << helpMessage;
      reply.addString("ok");
   }
   else if (command.get(0).asString()=="bias") {
      	_jtscalibrationThread->bias();
         reply.addString("bias ok");
      
   }
   return true;
}

/* Called periodically every getPeriod() seconds */
bool JTSCalibrationModule::updateModule() {
	if (!_jtscalibrationThread) {
          //  error_out("%s: Error. Control thread pointer is zero.\n", _moduleName.c_str());
            return false;
        }
// tester le tps d'exécution, période ??
    	return true;
}

double JTSCalibrationModule::getPeriod() {
    /* module periodicity (seconds), called implicitly by myModule */    
	return _period;
}

