/*
 * Author: Guillaume Hamon, ISIR , 2014
*/

#include <yarp/os/ResourceFinder.h>
#include <yarp/os/Network.h>
#include <iostream>
#include "JTScalibrationThread.h"
#include "JTSCalibrationModule.h"

using namespace yarp::os;

int main(int argc, char **argv)
{
    ResourceFinder *rf = new ResourceFinder;

    rf->setVerbose(true);
    rf->setDefaultConfigFile("default.ini");         	//default config file name.
    rf->setDefaultContext("jtsCalibration"); 		//when no parameters are given to the module this is the default context

    rf->configure("ICUB_ROOT",argc,argv);

    if (rf->check("help"))
    {
        std::cout<< "Possible parameters" << std::endl << std::endl;
        std::cout<< "\t--context          :Where to find a user defined .ini file within $ICUB_ROOT/app e.g. /JTS_calibration/conf" << std::endl;
        std::cout<< "\t--rate             :Period used by the module. Default set to 10ms." << std::endl;
        std::cout<< "\t--robot            :Robot name (icubSim or icub). Set to icub by default." << std::endl;
        std::cout<< "\t--local            :Prefix of the ports opened by the module. Set to the module name by default, i.e. JTScalibration." << std::endl;
        return 0;
    }

    Network yarp;
    
    if (!yarp.checkNetwork())
    {
        std::cerr << "Sorry YARP network is not available\n";
        return -1;
    }
    
    //Creating the module
    JTSCalibrationModule module;
    std::cout<<"beginning"<<std::endl;
    return module.runModule(*rf);
}
