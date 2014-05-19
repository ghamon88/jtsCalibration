# Copyright: (C) 2014 CoDyCo
# Author: Guillaume Hamon
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

# YARP needs CMake 2.6 or greater
cmake_minimum_required(VERSION 2.8.7)
SET(PROJECTNAME jtsCalibration)
PROJECT(${PROJECTNAME})

# find YARP

#find_package(YARP REQUIRED)
#find_package(ICUB)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${YARP_MODULE_PATH})
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ICUB_MODULE_PATH})

set(SRC_FOLDER ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_FOLDER ${PROJECT_SOURCE_DIR}/include)

set(SOURCES 
    ${SRC_FOLDER}/main.cpp 
    ${SRC_FOLDER}/JTSCalibrationModule.cpp 
    ${SRC_FOLDER}/JTScalibrationThread.cpp
	 ${SRC_FOLDER}/modHelp.cpp)

set(INCLUDES 
    ${INCLUDE_FOLDER}/JTSCalibrationModule.h 
    ${INCLUDE_FOLDER}/JTScalibrationThread.h
	 ${INCLUDE_FOLDER}/modHelp.h)

SOURCE_GROUP("Source Files" FILES ${SOURCES})
SOURCE_GROUP("Header Files" FILES ${INCLUDES})

#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ICUB_LINK_FLAGS}")

# add YARP include directories

include_directories(${YARP_INCLUDE_DIRS} ${INCLUDE_FOLDER})# ${modHelp_INCLUDE_DIRS})
                 
                    

# set up our program
#add_executable(JTScalibration JTSCalibrationModule.cpp JTScalibrationThread.cpp main.cpp)
ADD_EXECUTABLE(${PROJECTNAME} ${SOURCES} ${INCLUDES})

# link with YARP libraries
#target_link_libraries(JTScalibration ${YARP_LIBRARIES})
TARGET_LINK_LIBRARIES(${PROJECTNAME} ${YARP_LIBRARIES}) #modHelp

#if(WIN32)
#	INSTALL_TARGETS(/bin/Release ${PROJECTNAME})	
#else(WIN32)
#	INSTALL_TARGETS(/bin ${PROJECTNAME})
#endif(WIN32)

#add_subdirectory(app)
INSTALL(TARGETS ${PROJECTNAME} DESTINATION bin)

########## application
#set(appname jtscalib)
#file(GLOB conf ${CMAKE_CURRENT_SOURCE_DIR}/app/conf/*.ini)
