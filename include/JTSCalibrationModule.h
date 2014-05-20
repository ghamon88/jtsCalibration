#ifndef _JTSCALIBRATIONMODULE_H_
#define _JTSCALIBRATIONMODULE_H_

#include <iostream>
#include <string>

//#include <yarp/sig/all.h>
#include <yarp/os/all.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/Network.h>
#include <yarp/os/Thread.h>
#include <yarp/sig/Vector.h>

#include "modHelp.h"
// within project includes  
#include "JTScalibrationThread.h"

using namespace yarp::sig;
/**
 * here you need to document your classes.
 */
class JTSCalibrationModule : public yarp::os::RFModule {
    	std::string _moduleName;
    	std::string _robotName; 
	int _period;

    	std::string inputPortName_RA;
    	std::string inputPortName_LA;
    	std::string inputPortName_RUL;
    	std::string inputPortName_LUL;
		std::string inputPortName_RLL;
    	std::string inputPortName_LLL;

    	std::string outputPortName_RA;
    	std::string outputPortName_LA;
    	std::string outputPortName_RUL;
    	std::string outputPortName_LUL;
		std::string outputPortName_RLL;
    	std::string outputPortName_LLL;
      
    	std::string handlerPortName;

	/*double* _gainRA;
	double* _gainLA;
	double* _gainRL;
	double* _gainLL;

	double* _offsetRA;
	double* _offsetLA;
	double* _offsetRL;
	double* _offsetLL;*/
    
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

    yarp::os::Port handlerPort;      //a port to handle messages 

    /* pointer to a new thread to be created and started in configure() and stopped in close() */
    JTSCalibrationThread *_jtscalibrationThread;

public:
    /** 
     * document your methods too.
     */
    bool configure(yarp::os::ResourceFinder &rf); // configure all the module parameters and return true if successful
    bool interruptModule();                       // interrupt, e.g., the ports 
    bool close();                                 // close and shut down the module
    bool respond(const yarp::os::Bottle& command, yarp::os::Bottle& reply);
    double getPeriod(); 
    bool updateModule();
};


#endif // __JTSCALIBRATIONMODULE_H__

//----- end-of-file --- ( next line intentionally left blank ) ------------------

