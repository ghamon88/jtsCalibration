/*
 * Author: Guillaume Hamon, ISIR , 2014
*/


#include "JTScalibrationThread.h"

using namespace yarp::os;
using namespace yarp::sig;
using namespace std;


JTSCalibrationThread::JTSCalibrationThread(std::string& threadName, std::string& robotName,int periodMilliseconds,
						std::string& inputPortName_RA,std::string& inputPortName_LA,std::string& inputPortName_RUL,std::string& inputPortName_LUL,std::string& inputPortName_RLL,std::string& inputPortName_LLL,std::string& inputPortName_T,std::string& inputPortName_idyn_RA,std::string& inputPortName_idyn_LA,std::string& inputPortName_idyn_RL,std::string& inputPortName_idyn_LL,std::string& inputPortName_idyn_T,
						std::string& outputPortName_RA,std::string& outputPortName_LA,std::string& outputPortName_RUL,std::string& outputPortName_LUL,std::string& outputPortName_RLL,std::string& outputPortName_LLL,std::string& outputPortName_T,
						Vector GainRA, Vector GainLA, Vector GainRUL, Vector GainLUL, Vector GainRLL, Vector GainLLL,Vector GainT,
						Vector OffsetRA, Vector OffsetLA, Vector OffsetRUL, Vector OffsetLUL, Vector OffsetRLL, Vector OffsetLLL, Vector OffsetT):
_period(periodMilliseconds),
_threadName(threadName),
_robotName(robotName),
_inputPortName_RA(inputPortName_RA),
_inputPortName_LA(inputPortName_LA),
_inputPortName_RUL(inputPortName_RUL),
_inputPortName_LUL(inputPortName_LUL),
_inputPortName_RLL(inputPortName_RLL),
_inputPortName_LLL(inputPortName_LLL),
_inputPortName_T(inputPortName_T),
_inputPortName_RUL(inputPortName_idyn_RA),
_inputPortName_LUL(inputPortName_idyn_LA),
_inputPortName_RLL(inputPortName_idyn_RL),
_inputPortName_LLL(inputPortName_idyn_LL),
_inputPortName_T(inputPortName_idyn_T),
_outputPortName_RA(outputPortName_RA),
_outputPortName_LA(outputPortName_LA),
_outputPortName_RUL(outputPortName_RUL),
_outputPortName_LUL(outputPortName_LUL),
_outputPortName_RLL(outputPortName_RLL),
_outputPortName_LLL(outputPortName_LLL),
_outputPortName_T(outputPortName_T),
_gainRA(GainRA),
_gainLA(GainLA),
_gainRUL(GainRUL),
_gainLUL(GainLUL),
_gainRLL(GainRLL),
_gainLLL(GainLLL),
_gainT(GainT),
_offsetRA(OffsetRA),
_offsetLA(OffsetLA),
_offsetRUL(OffsetRUL),
_offsetLUL(OffsetLUL),
_offsetRLL(OffsetRLL),
_offsetLLL(OffsetLLL),
_offsetT(OffsetT)
{

}

JTSCalibrationThread::~JTSCalibrationThread() { threadRelease(); }

bool JTSCalibrationThread::threadInit() {
    /* initialize variables and create data-structures if needed */

    /* opening ports */
	if(!inputPort_RA.open(("/" + _threadName + _inputPortName_RA).c_str())){
		cout  << ": unable to open input port Right Arm" <<  endl;
		return false; 
    	}

	if(!inputPort_LA.open(("/" + _threadName + _inputPortName_LA).c_str())){
		cout  << ": unable to open input port Left Arm" <<  endl;
		return false;  
    	}

	if(!inputPort_RUL.open(("/" + _threadName + _inputPortName_RUL).c_str())){
		cout  << ": unable to open input port Right Upper Leg" <<  endl;
		return false;  
    	}

	if(!inputPort_LUL.open(("/" + _threadName + _inputPortName_LUL).c_str())){
		cout  << ": unable to open input port Left Upper Leg" <<  endl;
		return false;  
    	}
	if(!inputPort_RLL.open(("/" + _threadName + _inputPortName_RLL).c_str())){
		cout  << ": unable to open input port Right Lower Leg" <<  endl;
		return false;  
    	}

	if(!inputPort_LLL.open(("/" + _threadName + _inputPortName_LLL).c_str())){
		cout  << ": unable to open input port Left Lower Leg" <<  endl;
		return false;  
    	}

	if(!inputPort_T.open(("/" + _threadName + _inputPortName_T).c_str())){
		cout  << ": unable to open input port Torso" <<  endl;
		return false;  
    	}

	if(!inputPort_idyn_RA.open(("/" + _threadName + _inputPortName_idyn_RA).c_str())){
		cout  << ": unable to open input port idyn Right Arm" <<  endl;
		return false;  
    	}

	if(!inputPort_idyn_LA.open(("/" + _threadName + _inputPortName_idyn_LA).c_str())){
		cout  << ": unable to open input port idyn Left Arm" <<  endl;
		return false;  
    	}
	if(!inputPort_idyn_RL.open(("/" + _threadName + _inputPortName_idyn_RL).c_str())){
		cout  << ": unable to open input port idyn Right Leg" <<  endl;
		return false;  
    	}

	if(!inputPort_idyn_LL.open(("/" + _threadName + _inputPortName_idyn_LL).c_str())){
		cout  << ": unable to open input port idyn Left Leg" <<  endl;
		return false;  
    	}

	if(!inputPort_idyn_T.open(("/" + _threadName + _inputPortName_idyn_T).c_str())){
		cout  << ": unable to open input port idyn Torso" <<  endl;
		return false;  
    	}

	if(!outputPort_RA.open(("/" + _threadName + _outputPortName_RA).c_str())){
		cout  << ": unable to open output port Right Arm" <<  endl;
		return false;  
    	}

	if(!outputPort_LA.open(("/" + _threadName + _outputPortName_LA).c_str())){
		cout  << ": unable to open output port Left Arm" <<  endl;
		return false;  
    	}

	if(!outputPort_RUL.open(("/" + _threadName + _outputPortName_RUL).c_str())){
		cout  << ": unable to open output port Right Upper Leg" <<  endl;
		return false;  
    	}

	if(!outputPort_LUL.open(("/" + _threadName + _outputPortName_LUL).c_str())){
		cout  << ": unable to open output port Left Upper Leg" <<  endl;
		return false;  
    	}

	if(!outputPort_RLL.open(("/" + _threadName + _outputPortName_RLL).c_str())){
		cout  << ": unable to open output port Right Lower Leg" <<  endl;
		return false;  
    	}

	if(!outputPort_LLL.open(("/" + _threadName + _outputPortName_LLL).c_str())){
		cout  << ": unable to open output port Left Lower Leg" <<  endl;
		return false;  
    	}

	if(!outputPort_T.open(("/" + _threadName + _outputPortName_T).c_str())){
		cout  << ": unable to open output port Torso" <<  endl;
		return false;  
    	}

    	return true;
}

void JTSCalibrationThread::run() {
    unsigned char value;
    	while (isStopping() != true) { // the thread continues to run until isStopping() returns true

		
		// read the message
    		Bottle* in_RA;
    		in_RA=inputPort_RA.read(false);
    		if (in_RA==NULL) {
      			//fprintf(stderr, "Failed to read right arm JTS values\n");
      			//return;
    		}else{
			for(int i=0; i<3;i++){
				calibrated_JTS_RA[i]=((*in_RA).get(i).asDouble()*_gainRA[i])-_offsetRA[i];
			}
    			//cout<<"Right Arm Joint Torque Sensors calibrated values = "<< calibrated_JTS_RA[0]<< " "<<calibrated_JTS_RA[1]<< " "<<calibrated_JTS_RA[2]<<endl;
				// prepare a message to send
    			Bottle&out_RA = outputPort_RA.prepare();
    			out_RA.clear();
    			out_RA.addDouble(calibrated_JTS_RA[0]);
    			out_RA.addDouble(calibrated_JTS_RA[1]);
    			out_RA.addDouble(calibrated_JTS_RA[2]);
   			//printf("Sending %s\n", out_RA.toString().c_str());
    			// send the message
    			outputPort_RA.write(true);
    		}
    

    		Bottle* in_LA;
    		in_LA=inputPort_LA.read(false);
    		if (in_LA==NULL) {
      			//fprintf(stderr, "Failed to read left arm JTS values\n");
      			//return;
    		}else{
			for(int i=0; i<3;i++){
				calibrated_JTS_LA[i]=((*in_LA).get(i).asDouble()*_gainLA[i])-_offsetLA[i];
			}
    			//cout<<"Left Arm Joint Torque Sensors calibrated values = "<< calibrated_JTS_LA[0]<< " "<<calibrated_JTS_LA[1]<< " "<<calibrated_JTS_LA[2]<<endl;
			Bottle&out_LA = outputPort_LA.prepare();
	    		out_LA.clear();
	    		out_LA.addDouble(calibrated_JTS_LA[0]);
	    		out_LA.addDouble(calibrated_JTS_LA[1]);
	   		out_LA.addDouble(calibrated_JTS_LA[2]);
	   		//printf("Sending %s\n", out_LA.toString().c_str());
	    		// send the message
	    		outputPort_LA.write(true);
    		}
	
		Bottle* in_RUL;
    		in_RUL=inputPort_RUL.read(false);
    		if (in_RUL==NULL) {
      			//fprintf(stderr, "Failed to read right leg JTS values\n");
      			//return;
    		}else{
			for(int i=0; i<2;i++){
				calibrated_JTS_RUL[i]=((*in_RUL).get(i).asDouble()*_gainRUL[i])-_offsetRUL[i];
			}
    			//cout<<"Right Leg Joint Torque Sensors calibrated values = "<< calibrated_JTS_RUL[0]<< " "<<calibrated_JTS_RUL[1]<< " "<<calibrated_JTS_RUL[2]<<endl;
				// prepare a message to send
    			Bottle&out_RUL = outputPort_RUL.prepare();
   	 		out_RUL.clear();
   	 		out_RUL.addDouble(calibrated_JTS_RUL[0]);
    			out_RUL.addDouble(calibrated_JTS_RUL[1]);
   			//printf("Sending %s\n", out_RUL.toString().c_str());
	    		// send the message
   	 		outputPort_RUL.write(true);
    		}
    

    		Bottle* in_LUL;
    		in_LUL=inputPort_LUL.read(true);
    		if (in_LUL==NULL) {
      			//fprintf(stderr, "Failed to read left arm JTS values\n");
      			//return;
    		}else{
			for(int i=0; i<2;i++){
				calibrated_JTS_LUL[i]=((*in_LUL).get(i).asDouble()*_gainLUL[i])-_offsetLUL[i];
			}
    			//cout<<"Left Leg Joint Torque Sensors calibrated values = "<< calibrated_JTS_LUL[0]<< " "<<calibrated_JTS_LUL[1]<< " "<<calibrated_JTS_LUL[2]<<endl;
				
    			Bottle&out_LUL = outputPort_LUL.prepare();
    			out_LUL.clear();
    			out_LUL.addDouble(calibrated_JTS_LUL[0]);
    			out_LUL.addDouble(calibrated_JTS_LUL[1]);
   			//printf("Sending %s\n", out_LUL.toString().c_str());
    			// send the message
    			outputPort_LUL.write(true);
    		}

		Bottle* in_RLL;
    		in_RLL=inputPort_RLL.read(false);
    		if (in_RLL==NULL) {
      			//fprintf(stderr, "Failed to read right leg JTS values\n");
      			//return;
    		}else{
			for(int i=0; i<2;i++){
				calibrated_JTS_RLL[i]=((*in_RLL).get(i).asDouble()*_gainRLL[i])-_offsetRLL[i];
			}
    			//cout<<"Right Leg Joint Torque Sensors calibrated values = "<< calibrated_JTS_RLL[0]<< " "<<calibrated_JTS_RLL[1]<< " "<<calibrated_JTS_RLL[2]<<endl;
				// prepare a message to send
    			Bottle&out_RLL = outputPort_RLL.prepare();
   	 		out_RLL.clear();
   	 		out_RLL.addDouble(calibrated_JTS_RLL[0]);
    			out_RLL.addDouble(calibrated_JTS_RLL[1]);
   			//printf("Sending %s\n", out_RLL.toString().c_str());
	    		// send the message
   	 		outputPort_RLL.write(true);
    		}
    

    		Bottle* in_LLL;
    		in_LLL=inputPort_LLL.read(true);
    		if (in_LLL==NULL) {
      			//fprintf(stderr, "Failed to read left arm JTS values\n");
      			//return;
    		}else{
			for(int i=0; i<2;i++){
				calibrated_JTS_LLL[i]=((*in_LLL).get(i).asDouble()*_gainLLL[i])-_offsetLLL[i];
			}
    			//cout<<"Left Leg Joint Torque Sensors calibrated values = "<< calibrated_JTS_LUL[0]<< " "<<calibrated_JTS_LUL[1]<< " "<<calibrated_JTS_LUL[2]<<endl;
				
    			Bottle&out_LLL = outputPort_LLL.prepare();
    			out_LLL.clear();
    			out_LLL.addDouble(calibrated_JTS_LLL[0]);
    			out_LLL.addDouble(calibrated_JTS_LLL[1]);
   			//printf("Sending %s\n", out_LUL.toString().c_str());
    			// send the message
    			outputPort_LLL.write(true);
    		}

		Bottle* in_T;
    		in_T=inputPort_T.read(true);
    		if (in_T==NULL) {
      			//fprintf(stderr, "Failed to read left arm JTS values\n");
      			//return;
    		}else{
			for(int i=0; i<2;i++){
				calibrated_JTS_T[i]=((*in_T).get(i).asDouble()*_gainT[i])-_offsetT[i];
			}
    			//cout<<"Left Leg Joint Torque Sensors calibrated values = "<< calibrated_JTS_T[0]<< " "<<calibrated_JTS_T[1]<< endl;
				
    			Bottle&out_T = outputPort_T.prepare();
    			out_T.clear();
    			out_T.addDouble(calibrated_JTS_T[0]);
    			out_T.addDouble(calibrated_JTS_T[1]);
   			//printf("Sending %s\n", out_LUL.toString().c_str());
    			// send the message
    			outputPort_T.write(true);
    		}

    	}  //while
}

void JTSCalibrationThread::threadRelease() {

}

void JTSCalibrationThread::onStop() {
    	inputPort_RA.interrupt();
    	inputPort_LA.interrupt();
	inputPort_RUL.interrupt();
    	inputPort_LUL.interrupt();
	inputPort_RLL.interrupt();
    	inputPort_LLL.interrupt();
	inputPort_T.interrupt();
	inputPort_idyn_RA.interrupt();
    	inputPort_idyn_LA.interrupt();
	inputPort_idyn_RL.interrupt();
    	inputPort_idyn_LL.interrupt();
	inputPort_idyn_T.interrupt();
	outputPort_RA.interrupt();
    	outputPort_LA.interrupt();
	outputPort_RUL.interrupt();
    	outputPort_LUL.interrupt();
	outputPort_RLL.interrupt();
    	outputPort_LLL.interrupt();
	outputPort_T.interrupt();
  
	inputPort_RA.close();
    	inputPort_LA.close();
	inputPort_RUL.close();
    	inputPort_LUL.close();
	inputPort_RLL.close();
    	inputPort_LLL.close();
	inputPort_T.close();
	inputPort_idyn_RA.close();
    	inputPort_idyn_LA.close();
	inputPort_idyn_RL.close();
    	inputPort_idyn_LL.close();
	inputPort_idyn_T.close();
	outputPort_RA.close();
    	outputPort_LA.close();
	outputPort_RUL.close();
    	outputPort_LUL.close();
	outputPort_RLL.close();
    	outputPort_LLL.close();
	outputPort_T.close();
}

void JTSCalibrationThread::bias() {
	// change to offset = -idyn_value + gain * jts_value , do it in static configuration --> read idyn torque values...
	Bottle* in;
	double V[3];
	double Tau[6];
    	in=inputPort_RA.read(true);
    	if (in==NULL) {
      		fprintf(stderr, "Failed to read right arm JTS values\n");
      		return;
    	}else{
		for(int i=0;i<3;i++){
			V[i]=(*in).get(i).asDouble(); 
		}
	}
	in=inputPort_idyn_RA.read(true);
	if (in==NULL) {
      		fprintf(stderr, "Failed to read idyn right arm torque values\n");
      		return;
    	}else{
		for(int i=0;i<5;i++){
			Tau[i]=(*in).get(i).asDouble(); 
		}
	}
	_offsetRA[0]=_gainRA[0]*V[0]-Tau[1]; //J0
	_offsetRA[1]=_gainRA[1]*V[1]-Tau[2]; //J1
	_offsetRA[2]=_gainRA[2]*V[2]-Tau[4]; //J3

	in=inputPort_LA.read(true);
    	if (in==NULL) {
      		fprintf(stderr, "Failed to read left arm JTS values\n");
      		return;
    	}else{
		for(int i=0;i<3;i++){
			V[i]=(*in).get(i).asDouble(); 
		}
	}
	in=inputPort_idyn_LA.read(true);
	if (in==NULL) {
      		fprintf(stderr, "Failed to read idyn left arm torque values\n");
      		return;
    	}else{
		for(int i=0;i<5;i++){
			Tau[i]=(*in).get(i).asDouble(); 
		}
	}
	_offsetLA[0]=_gainLA[0]*V[0]-Tau[1]; //J0
	_offsetLA[1]=_gainLA[1]*V[1]-Tau[2]; //J1
	_offsetLA[2]=_gainLA[2]*V[2]-Tau[4]; //J3

	in=inputPort_RUL.read(true);
    	if (in==NULL) {
      		fprintf(stderr, "Failed to read right upper leg JTS values\n");
      		return;
    	}else{
		for(int i=0;i<2;i++){
			V[i]=(*in).get(i).asDouble();
		}
	}
	in=inputPort_idyn_RL.read(true);
	if (in==NULL) {
      		fprintf(stderr, "Failed to read idyn right leg torque values\n");
      		return;
    	}else{
		for(int i=0;i<6;i++){
			Tau[i]=(*in).get(i).asDouble(); 
		}
	}
	_offsetRUL[0]=_gainRUL[0]*V[0]-Tau[1]; //J0
	_offsetRUL[1]=_gainRUL[1]*V[1]-Tau[2]; //J1

	in=inputPort_RLL.read(true);
    	if (in==NULL) {
      		fprintf(stderr, "Failed to read right lower leg JTS values\n");
      		return;
    	}else{
		for(int i=0;i<2;i++){
			V[i]=(*in).get(i).asDouble();
		}
	}

	_offsetRLL[0]=_gainRLL[0]*V[0]-Tau[4]; //J3
	_offsetRLL[1]=_gainRLL[1]*V[1]-Tau[5]; //J4

	in=inputPort_LUL.read(true);
    	if (in==NULL) {
      		fprintf(stderr, "Failed to read left upper leg JTS values\n");
      		return;
    	}else{
		for(int i=0;i<2;i++){
			V[i]=(*in).get(i).asDouble();
		}
	}
	in=inputPort_idyn_LL.read(true);
	if (in==NULL) {
      		fprintf(stderr, "Failed to read idyn left leg torque values\n");
      		return;
    	}else{
		for(int i=0;i<6;i++){
			Tau[i]=(*in).get(i).asDouble(); 
		}
	}
	_offsetLUL[0]=_gainLUL[0]*V[0]-Tau[1]; //J0
	_offsetLUL[1]=_gainLUL[1]*V[1]-Tau[2]; //J1

	in=inputPort_LLL.read(true);
    	if (in==NULL) {
      		fprintf(stderr, "Failed to read left lower leg JTS values\n");
      		return;
    	}else{
		for(int i=0;i<2;i++){
			V[i]=(*in).get(i).asDouble();
		}
	}
	_offsetLLL[0]=_gainLLL[0]*V[0]-Tau[4]; //J3
	_offsetLLL[1]=_gainLLL[1]*V[1]-Tau[5]; //J4

	in=inputPort_T.read(true);
    	if (in==NULL) {
      		fprintf(stderr, "Failed to read Torso JTS values\n");
      		return;
    	}else{
		for(int i=0;i<2;i++){
			V[i]=(*in).get(i).asDouble();
		}
	}
	in=inputPort_idyn_T.read(true);
    	if (in==NULL) {
      		fprintf(stderr, "Failed to read idyn torso torque values\n");
      		return;
    	}else{
		for(int i=0;i<3;i++){
			Tau[i]=(*in).get(i).asDouble(); 
		}
	}
	_offsetT[0]=_gainT[0]*V[0]-Tau[3]; //J2
	_offsetT[1]=_gainT[1]*V[1]-Tau[2]; //J1
	
}
