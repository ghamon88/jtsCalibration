#include "JTScalibrationThread.h"

using namespace yarp::os;
using namespace yarp::sig;
using namespace std;


JTSCalibrationThread::JTSCalibrationThread(std::string& threadName, std::string& robotName,int periodMilliseconds,
						std::string& inputPortName_RA,std::string& inputPortName_LA,std::string& inputPortName_RUL,std::string& inputPortName_LUL,std::string& inputPortName_RLL,std::string& inputPortName_LLL,std::string& inputPortName_T,
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
		cout  << ": unable to open input port RA" <<  endl;
		return false;  // unable to open; let RFModule know so that it won't run
    	}

	if(!inputPort_LA.open(("/" + _threadName + _inputPortName_LA).c_str())){
		cout  << ": unable to open input port LA" <<  endl;
		return false;  
    	}

	if(!inputPort_RUL.open(("/" + _threadName + _inputPortName_RUL).c_str())){
		cout  << ": unable to open input port RUL" <<  endl;
		return false;  
    	}

	if(!inputPort_LUL.open(("/" + _threadName + _inputPortName_LUL).c_str())){
		cout  << ": unable to open input port LUL" <<  endl;
		return false;  
    	}
	if(!inputPort_RLL.open(("/" + _threadName + _inputPortName_RLL).c_str())){
		cout  << ": unable to open input port RLL" <<  endl;
		return false;  
    	}

	if(!inputPort_LLL.open(("/" + _threadName + _inputPortName_LLL).c_str())){
		cout  << ": unable to open input port LLL" <<  endl;
		return false;  
    	}

	if(!inputPort_T.open(("/" + _threadName + _inputPortName_T).c_str())){
		cout  << ": unable to open input port T" <<  endl;
		return false;  
    	}

	if(!outputPort_RA.open(("/" + _threadName + _outputPortName_RA).c_str())){
		cout  << ": unable to open output port RA" <<  endl;
		return false;  
    	}

	if(!outputPort_LA.open(("/" + _threadName + _outputPortName_LA).c_str())){
		cout  << ": unable to open output port LA" <<  endl;
		return false;  
    	}

	if(!outputPort_RUL.open(("/" + _threadName + _outputPortName_RUL).c_str())){
		cout  << ": unable to open output port RUL" <<  endl;
		return false;  
    	}

	if(!outputPort_LUL.open(("/" + _threadName + _outputPortName_LUL).c_str())){
		cout  << ": unable to open output port LUL" <<  endl;
		return false;  
    	}

	if(!outputPort_RLL.open(("/" + _threadName + _outputPortName_RLL).c_str())){
		cout  << ": unable to open output port RLL" <<  endl;
		return false;  
    	}

	if(!outputPort_LLL.open(("/" + _threadName + _outputPortName_LLL).c_str())){
		cout  << ": unable to open output port LLL" <<  endl;
		return false;  
    	}

	if(!outputPort_T.open(("/" + _threadName + _outputPortName_T).c_str())){
		cout  << ": unable to open output port T" <<  endl;
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
    
		/*************************** faire plutôt une fonction que de la répétition... pareil pour au-dessus *************************/
    		


    		

		



    	}  //while
}

void JTSCalibrationThread::threadRelease() {
   /* for example, delete dynamically created data-structures */
}

void JTSCalibrationThread::onStop() {
    	inputPort_RA.interrupt();
    	inputPort_LA.interrupt();
	inputPort_RUL.interrupt();
    	inputPort_LUL.interrupt();
	inputPort_RLL.interrupt();
    	inputPort_LLL.interrupt();
	inputPort_T.interrupt();
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
	outputPort_RA.close();
    	outputPort_LA.close();
	outputPort_RUL.close();
    	outputPort_LUL.close();
	outputPort_RLL.close();
    	outputPort_LLL.close();
	outputPort_T.close();
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

	in=inputPort_RUL.read(true);
    	if (in==NULL) {
      		fprintf(stderr, "Failed to read right upper leg JTS values\n");
      		return;
    	}else{
		for(int i=0;i<2;i++){
			_offsetRUL[i]=(*in).get(i).asDouble();
		}
	}

	in=inputPort_LUL.read(true);
    	if (in==NULL) {
      		fprintf(stderr, "Failed to read left upper leg JTS values\n");
      		return;
    	}else{
		for(int i=0;i<2;i++){
			_offsetLUL[i]=(*in).get(i).asDouble();
		}
	}

	in=inputPort_RLL.read(true);
    	if (in==NULL) {
      		fprintf(stderr, "Failed to read right lower leg JTS values\n");
      		return;
    	}else{
		for(int i=0;i<2;i++){
			_offsetRLL[i]=(*in).get(i).asDouble();
		}
	}

	in=inputPort_LLL.read(true);
    	if (in==NULL) {
      		fprintf(stderr, "Failed to read left lower leg JTS values\n");
      		return;
    	}else{
		for(int i=0;i<2;i++){
			_offsetLLL[i]=(*in).get(i).asDouble();
		}
	}

	in=inputPort_T.read(true);
    	if (in==NULL) {
      		fprintf(stderr, "Failed to read Torso JTS values\n");
      		return;
    	}else{
		for(int i=0;i<2;i++){
			_offsetT[i]=(*in).get(i).asDouble();
		}
	}
	
}
