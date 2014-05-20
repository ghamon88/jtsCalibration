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

bool JTSCalibrationModule::configure(yarp::os::ResourceFinder &rf) {    

	_gainRA.resize(3,0.0);
	_gainLA.resize(3,0.0);
	_gainRUL.resize(2,0.0);
	_gainLUL.resize(2,0.0);
	_gainRLL.resize(2,0.0);
	_gainLLL.resize(2,0.0);
	_gainT.resize(2,0.0);
	_offsetRA.resize(3,0.0);
	_offsetLA.resize(3,0.0);
	_offsetRUL.resize(2,0.0);
	_offsetLUL.resize(2,0.0);
	_offsetRLL.resize(2,0.0);
	_offsetLLL.resize(2,0.0);
	_offsetT.resize(2,0.0);

	Bottle &bGeneral=rf.findGroup("general");
	macsi::modHelp::readString(bGeneral,"name",_moduleName,"JTSCalib");
   macsi::modHelp::readString(bGeneral,"robot",_robotName,"icub");	
	macsi::modHelp::readInt(bGeneral,"period",_period,10);

	std::cout<<_moduleName<<std::endl;

	Bottle &bGains=rf.findGroup("gains");
 	macsi::modHelp::readVector(bGains,"GainRA",_gainRA,3);
	macsi::modHelp::readVector(bGains,"GainLA",_gainLA,3);
	macsi::modHelp::readVector(bGains,"GainRUL",_gainRUL,2);
	macsi::modHelp::readVector(bGains,"GainLUL",_gainLUL,2);
	macsi::modHelp::readVector(bGains,"GainRLL",_gainRLL,2);
	macsi::modHelp::readVector(bGains,"GainLLL",_gainLLL,2);
	macsi::modHelp::readVector(bGains,"GainT",_gainT,2);
	macsi::modHelp::readVector(bGains,"OffsetRA",_offsetRA,3);
	macsi::modHelp::readVector(bGains,"OffsetLA",_offsetLA,3);
	macsi::modHelp::readVector(bGains,"OffsetRUL",_offsetRUL,2);
	macsi::modHelp::readVector(bGains,"OffsetLUL",_offsetLUL,2);
	macsi::modHelp::readVector(bGains,"OffsetRLL",_offsetRLL,2);
	macsi::modHelp::readVector(bGains,"OffsetLLL",_offsetLLL,2);
	macsi::modHelp::readVector(bGains,"OffsetT",_offsetT,2);

	std::cout<<"gains et offsets ok"<<std::endl;

	Bottle &bPorts=rf.findGroup("ports");

	macsi::modHelp::readString(bPorts,"InputPortRightArm",inputPortName_RA,"/right_arm/raw:i");	
	macsi::modHelp::readString(bPorts,"InputPortLeftArm",inputPortName_LA,"/left_arm/raw:i");	
	macsi::modHelp::readString(bPorts,"InputPortRightUpperLeg",inputPortName_RUL,"/right_upper_leg/raw:i");	
	macsi::modHelp::readString(bPorts,"InputPortLeftUpperLeg",inputPortName_LUL,"/left_upper_leg/raw:i");	
	macsi::modHelp::readString(bPorts,"InputPortRightLowerLeg",inputPortName_RLL,"/right_lower_leg/raw:i");	
	macsi::modHelp::readString(bPorts,"InputPortLeftLowerLeg",inputPortName_LLL,"/left_lower_leg/raw:i");	
	macsi::modHelp::readString(bPorts,"InputPortTorso",inputPortName_T,"/torso/raw:i");	

	macsi::modHelp::readString(bPorts,"OutputPortRightArm",outputPortName_RA,"/right_arm/calibrated:o");	
	macsi::modHelp::readString(bPorts,"OutputPortLeftArm",outputPortName_LA,"/left_arm/calibrated:o");	
	macsi::modHelp::readString(bPorts,"OutputPortRightUpperLeg",outputPortName_RUL,"/right_upper_leg/calibrated:o");	
	macsi::modHelp::readString(bPorts,"OutputPortLeftUpperLeg",outputPortName_LUL,"/left_upper_leg/calibrated:o");	
	macsi::modHelp::readString(bPorts,"OutputPortRightLowerLeg",outputPortName_RLL,"/right_lower_leg/calibrated:o");	
	macsi::modHelp::readString(bPorts,"OutputPortLeftLowerLeg",outputPortName_LLL,"/left_lower_leg/calibrated:o");
	macsi::modHelp::readString(bPorts,"OutputPortTorso",outputPortName_T,"/torso/calibrated:o");
	

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
						inputPortName_RA,inputPortName_LA,inputPortName_RUL,inputPortName_LUL,inputPortName_RLL,inputPortName_LLL,inputPortName_T,
						outputPortName_RA,outputPortName_LA,outputPortName_RUL,outputPortName_LUL,outputPortName_RLL,outputPortName_LLL,outputPortName_T,
                                                _gainRA,_gainLA,_gainRUL,_gainLUL,_gainRLL,_gainLLL,_gainT,
						_offsetRA,_offsetLA,_offsetRUL,_offsetLUL,_offsetRLL,_offsetLLL,_offsetT);
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

