/**
 * @file demoThread.h
 * @brief this file contains the definition of an additional thread that does the job for the main module.
 */

#ifndef _JTSCALIBRATION_THREAD_H_
#define _JTSCALIBRATION_THREAD_H_

#include <yarp/sig/all.h>
#include <yarp/os/all.h>
#include <iostream>
#include <yarp/os/Network.h>
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
	std::string& _inputPortName_RL;
	std::string& _inputPortName_LL;
	std::string& _outputPortName_RA;
	std::string& _outputPortName_LA;
	std::string& _outputPortName_RL;
	std::string& _outputPortName_LL;

	double* _gainRA;
	double* _gainLA;
	double* _gainRL;
	double* _gainLL;

	double* _offsetRA;
	double* _offsetLA;
	double* _offsetRL;
	double* _offsetLL;

	double calibrated_JTS_RA[3];
	double calibrated_JTS_LA[3];
	double calibrated_JTS_RL[3];
	double calibrated_JTS_LL[3];

   	yarp::os::BufferedPort<yarp::os::Bottle> inputPort_RA, inputPort_LA, inputPort_RL, inputPort_LL;
	yarp::os::BufferedPort<yarp::os::Bottle> outputPort_RA, outputPort_LA, outputPort_RL, outputPort_LL;

public:
   /**
    * contructor.
    * @param threshold threshold for image filtering.
    */
   JTSCalibrationThread(std::string& threadName,
                              	std::string& robotName,
                              	int periodMilliseconds,
                              	std::string& inputPortName_RA,std::string& inputPortName_LA,std::string& inputPortName_RL,std::string& inputPortName_LL,
				std::string& outputPortName_RA,std::string& outputPortName_LA,std::string& outputPortName_RL,std::string& outputPortName_LL,
				double* GainRA,double* GainLA,double* GainRL,double* GainLL,
				double* OffsetRA,double* OffsetLA,double* OffsetRL,double* OffsetLL);

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
