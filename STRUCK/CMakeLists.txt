#project(STRUCK)

#cmake_minimum_required(VERSION 2.6)


find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

#if(NOT CMAKE_BUILD_TYPE)
    #set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
#endif()
#  set(OpenCV_ROOT_DIR "/usr/local/include")
#  MESSAGE("OpenCV is" ${OpenCV_INCLUDE_DIRS})
#INCLUDE_DIRECTORIES ( src/GraphUtils ${OpenCV_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR} )




set(SOURCE 
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Features.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HaarFeature.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HaarFeatures.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HistogramFeatures.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ImageRep.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LaRank.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MultiFeatures.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RawFeatures.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sampler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Tracker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GraphUtils/GraphUtils.cpp
    PARENT_SCOPE
    )
set(HEADERS
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.h
    ${CMAKE_CURRENT_SOURCE_DIR}/BasicConfig.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Features.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HaarFeature.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HaarFeatures.h
    ${CMAKE_CURRENT_SOURCE_DIR}/HistogramFeatures.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ImageRep.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Kernels.h
    ${CMAKE_CURRENT_SOURCE_DIR}/LaRank.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MultiFeatures.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Rect.h
    ${CMAKE_CURRENT_SOURCE_DIR}/RawFeatures.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Sampler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Tracker.h
    ${CMAKE_CURRENT_SOURCE_DIR}/GraphUtils/GraphUtils.h
    PARENT_SCOPE
    )
