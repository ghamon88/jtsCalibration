#include "JTScalibrationThread.h"

using namespace yarp::os;
using namespace yarp::sig;
using namespace std;

					
JTSCalibrationThread::JTSCalibrationThread(std::string& threadName, std::string& robotName,int periodMilliseconds,
						std::string& inputPortName_RA,std::string& inputPortName_LA,std::string& inputPortName_RL,std::string& inputPortName_LL,
						std::string& outputPortName_RA,std::string& outputPortName_LA,std::string& outputPortName_RL,std::string& outputPortName_LL,
						double* GainRA, double* GainLA, double* GainRL, double* GainLL,
						double* OffsetRA, double* OffsetLA, double* OffsetRL, double* OffsetLL):
_period(periodMilliseconds),
_threadName(threadName),
_robotName(robotName),
_inputPortName_RA(inputPortName_RA),
_inputPortName_LA(inputPortName_LA),
_inputPortName_RL(inputPortName_RL),
_inputPortName_LL(inputPortName_LL),
_outputPortName_RA(outputPortName_RA),
_outputPortName_LA(outputPortName_LA),
_outputPortName_RL(outputPortName_RL),
_outputPortName_LL(outputPortName_LL),
_gainRA(GainRA),
_gainLA(GainLA),
_gainRL(GainRL),
_gainLL(GainLL),
_offsetRA(OffsetRA),
_offsetLA(OffsetLA),
_offsetRL(OffsetRL),
_offsetLL(OffsetLL)
{   

}

JTSCalibrationThread::~JTSCalibrationThread() { threadRelease(); }

bool JTSCalibrationThread::threadInit() {
    /* initialize variables and create data-structures if needed */

    /* opening ports */
	if(!inputPort_RA.open(("/" + _threadName + "/" + _inputPortName_RA).c_str())){
		cout  << ": unable to open input port RA" <<  endl;
		return false;  // unable to open; let RFModule know so that it won't run
    	}

	if(!inputPort_LA.open(("/" + _threadName + "/" + _inputPortName_LA).c_str())){
		cout  << ": unable to open input port LA" <<  endl;
		return false;  
    	}

	if(!inputPort_RL.open(("/" + _threadName + "/" + _inputPortName_RL).c_str())){
		cout  << ": unable to open input port RL" <<  endl;
		return false;  
    	}

	if(!inputPort_LL.open(("/" + _threadName + "/" + _inputPortName_LL).c_str())){
		cout  << ": unable to open input port LL" <<  endl;
		return false;  
    	}

	if(!outputPort_RA.open(("/" + _threadName + "/" + _outputPortName_RA).c_str())){
		cout  << ": unable to open output port RA" <<  endl;
		return false;  
    	}

	if(!outputPort_LA.open(("/" + _threadName + "/" + _outputPortName_LA).c_str())){
		cout  << ": unable to open output port LA" <<  endl;
		return false;  
    	}

	if(!outputPort_RL.open(("/" + _threadName + "/" + _outputPortName_RL).c_str())){
		cout  << ": unable to open output port RL" <<  endl;
		return false;  
    	}

	if(!outputPort_LL.open(("/" + _threadName + "/" + _outputPortName_LL).c_str())){
		cout  << ": unable to open output port LL" <<  endl;
		return false;  
    	}

    	return true;
}

void JTSCalibrationThread::run() {
    /* 
    * do some work ....
    * for example, convert the input image to a binary image using the threshold provided 
    */ 
    unsigned char value;
    	while (isStopping() != true) { // the thread continues to run until isStopping() returns true

		
		// read the message
    		Bottle* in_RA;
    		in_RA=inputPort_RA.read(true);
    		if (in_RA==NULL) {
      			fprintf(stderr, "Failed to read right arm JTS values\n");
      			return;
    		}else{
			for(int i=0; i<3;i++){
				calibrated_JTS_RA[i]=((*in_RA).get(i).asDouble()-_offsetRA[i])*_gainRA[i];
			}
    			cout<<"Right Arm Joint Torque Sensors calibrated values = "<< calibrated_JTS_RA[0]<< " "<<calibrated_JTS_RA[1]<< " "<<calibrated_JTS_RA[2]<<endl;
    		}
    

    		Bottle* in_LA;
    		in_LA=inputPort_LA.read(true);
    		if (in_LA==NULL) {
      			fprintf(stderr, "Failed to read left arm JTS values\n");
      			return;
    		}else{
			for(int i=0; i<3;i++){
				calibrated_JTS_LA[i]=((*in_LA).get(i).asDouble()-_offsetLA[i])*_gainLA[i];
			}
    			cout<<"Left Arm Joint Torque Sensors calibrated values = "<< calibrated_JTS_LA[0]<< " "<<calibrated_JTS_LA[1]<< " "<<calibrated_JTS_LA[2]<<endl;
    		}
	
		Bottle* in_RL;
    		in_RL=inputPort_RL.read(true);
    		if (in_RL==NULL) {
      			fprintf(stderr, "Failed to read right leg JTS values\n");
      			return;
    		}else{
			for(int i=0; i<3;i++){
				calibrated_JTS_RL[i]=((*in_RL).get(i).asDouble()-_offsetRL[i])*_gainRL[i];
			}
    			cout<<"Right Leg Joint Torque Sensors calibrated values = "<< calibrated_JTS_RL[0]<< " "<<calibrated_JTS_RL[1]<< " "<<calibrated_JTS_RL[2]<<endl;
    		}
    

    		Bottle* in_LL;
    		in_LA=inputPort_LL.read(true);
    		if (in_LL==NULL) {
      			fprintf(stderr, "Failed to read left arm JTS values\n");
      			return;
    		}else{
			for(int i=0; i<3;i++){
				calibrated_JTS_LL[i]=((*in_LL).get(i).asDouble()-_offsetLL[i])*_gainLL[i];
			}
    			cout<<"Left Leg Joint Torque Sensors calibrated values = "<< calibrated_JTS_LL[0]<< " "<<calibrated_JTS_LL[1]<< " "<<calibrated_JTS_LL[2]<<endl;
    		}
    
		/*************************** faire plutôt une fonction que de la répétition... pareil pour au-dessus *************************/
    		// prepare a message to send
    		Bottle&out_RA = outputPort_RA.prepare();
    		out_RA.clear();
    		out_RA.addDouble(calibrated_JTS_RA[0]);
    		out_RA.addDouble(calibrated_JTS_RA[1]);
    		out_RA.addDouble(calibrated_JTS_RA[2]);
   		printf("Sending %s\n", out_RA.toString().c_str());
    		// send the message
    		outputPort_RA.write(true);


    		Bottle&out_LA = outputPort_LA.prepare();
    		out_LA.clear();
    		out_LA.addDouble(calibrated_JTS_LA[0]);
    		out_LA.addDouble(calibrated_JTS_LA[1]);
   		out_LA.addDouble(calibrated_JTS_LA[2]);
   		printf("Sending %s\n", out_LA.toString().c_str());
    		// send the message
    		outputPort_LA.write(true);

		// prepare a message to send
    		Bottle&out_RL = outputPort_RL.prepare();
    		out_RL.clear();
    		out_RL.addDouble(calibrated_JTS_RL[0]);
    		out_RL.addDouble(calibrated_JTS_RL[1]);
    		out_RL.addDouble(calibrated_JTS_RL[2]);
   		printf("Sending %s\n", out_RL.toString().c_str());
    		// send the message
    		outputPort_RL.write(true);


    		Bottle&out_LL = outputPort_LL.prepare();
    		out_LL.clear();
    		out_LL.addDouble(calibrated_JTS_LL[0]);
    		out_LL.addDouble(calibrated_JTS_LL[1]);
   		out_LL.addDouble(calibrated_JTS_LL[2]);
   		printf("Sending %s\n", out_LL.toString().c_str());
    		// send the message
    		outputPort_LL.write(true);

    	}  //while
}

void JTSCalibrationThread::threadRelease() {
   /* for example, delete dynamically created data-structures */
}

void JTSCalibrationThread::onStop() {
    	inputPort_RA.interrupt();
    	inputPort_LA.interrupt();
	inputPort_RL.interrupt();
    	inputPort_LL.interrupt();
	outputPort_RA.interrupt();
    	outputPort_LA.interrupt();
	outputPort_RL.interrupt();
    	outputPort_LL.interrupt();
  
	inputPort_RA.close();
    	inputPort_LA.close();
	inputPort_RL.close();
    	inputPort_LL.close();
	outputPort_RA.close();
    	outputPort_LA.close();
	outputPort_RL.close();
    	outputPort_LL.close();
}

void JTSCalibrationThread::bias() {
	Bottle* in;
    	in=inputPort_RA.read(true);
    	if (in==NULL) {
      		fprintf(stderr, "Failed to read right arm JTS values\n");
      		return;
    	}else{
		for(int i=0;i<3;i++){
			_offsetRA[i]=(*in).get(i).asDouble();
		}
	}

	in=inputPort_LA.read(true);
    	if (in==NULL) {
      		fprintf(stderr, "Failed to read left arm JTS values\n");
      		return;
    	}else{
		for(int i=0;i<3;i++){
			_offsetLA[i]=(*in).get(i).asDouble();
		}
	}

	in=inputPort_RL.read(true);
    	if (in==NULL) {
      		fprintf(stderr, "Failed to read right leg JTS values\n");
      		return;
    	}else{
		for(int i=0;i<3;i++){
			_offsetRL[i]=(*in).get(i).asDouble();
		}
	}

	in=inputPort_LL.read(true);
    	if (in==NULL) {
      		fprintf(stderr, "Failed to read left leg JTS values\n");
      		return;
    	}else{
		for(int i=0;i<3;i++){
			_offsetLL[i]=(*in).get(i).asDouble();
		}
	}
	
}
