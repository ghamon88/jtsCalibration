/**
 * @file demoThread.h
 * @brief this file contains the definition of an additional thread that does the job for the main module.
 */

#ifndef _JTSCALIBRATION_THREAD_H_
#define _JTSCALIBRATION_THREAD_H_

#include <yarp/sig/Vector.h>
#include <yarp/os/all.h>
#include <iostream>
#include <yarp/os/Network.h>

using namespace yarp::sig;

/**
 * theoretically, here you should document your class(es) and methods. 
 */
class JTSCalibrationThread : public yarp::os::Thread {
private:

	int _period;
	std::string& _threadName;
	std::string& _robotName;
	std::string& _inputPortName_RA;
	std::string& _inputPortName_LA;
	std::string& _inputPortName_RUL;
	std::string& _inputPortName_LUL;
	std::string& _inputPortName_RLL;
	std::string& _inputPortName_LLL;
	std::string& _outputPortName_RA;
	std::string& _outputPortName_LA;
	std::string& _outputPortName_RUL;
	std::string& _outputPortName_LUL;
	std::string& _outputPortName_RLL;
	std::string& _outputPortName_LLL;

	Vector _gainRA;
	Vector _gainLA;
	Vector _gainRUL;
	Vector _gainLUL;
	Vector _gainRLL;
	Vector _gainLLL;

	Vector _offsetRA;
	Vector _offsetLA;
	Vector _offsetRUL;
	Vector _offsetLUL;
	Vector _offsetRLL;
	Vector _offsetLLL;

	double calibrated_JTS_RA[3];
	double calibrated_JTS_LA[3];
	double calibrated_JTS_RUL[3];
	double calibrated_JTS_LUL[3];
	double calibrated_JTS_RLL[3];
	double calibrated_JTS_LLL[3];

   yarp::os::BufferedPort<yarp::os::Bottle> inputPort_RA, inputPort_LA, inputPort_RUL, inputPort_LUL, inputPort_RLL, inputPort_LLL;
	yarp::os::BufferedPort<yarp::os::Bottle> outputPort_RA, outputPort_LA, outputPort_RUL, outputPort_LUL, outputPort_RLL, outputPort_LLL;

public:
   /**
    * contructor.
    * @param threshold threshold for image filtering.
    */
   JTSCalibrationThread(std::string& threadName,
                              	std::string& robotName,
                              	int periodMilliseconds,
                              	std::string& inputPortName_RA,std::string& inputPortName_LA,std::string& inputPortName_RUL,std::string& inputPortName_LUL,std::string& inputPortName_RLL,std::string& inputPortName_LLL,
				std::string& outputPortName_RA,std::string& outputPortName_LA,std::string& outputPortName_RUL,std::string& outputPortName_LUL,std::string& outputPortName_RLL,std::string& outputPortName_LLL,
				Vector GainRA,Vector GainLA,Vector GainRUL,Vector GainLUL,Vector GainRLL,Vector GainLLL,
				Vector OffsetRA,Vector OffsetLA,Vector OffsetRUL,Vector OffsetLUL,Vector OffsetRLL,Vector OffsetLLL);

   /**
    * destructor.
    */
   ~JTSCalibrationThread();

   // and so forth... don't forget to document all your methods.
   bool threadInit();     
   void threadRelease();
   void run(); 
   void onStop();
   void bias();
};

#endif  //_JTSCALIBRATION_THREAD_H_

//----- end-of-file --- ( next line intentionally left blank ) ------------------
