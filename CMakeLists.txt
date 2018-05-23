cmake_minimum_required(VERSION 3.1.0)

project(TComp)

set(CMAKE_CXX_STANDARD 14)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(PkgConfig)
pkg_check_modules(PC_ZeroMQ QUIET zmq)

## use the hint from above to find where 'zmq.hpp' is located
find_path(ZeroMQ_INCLUDE_DIR
        NAMES zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS}
        )

## use the hint from about to find the location of libzmq
find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS}
        )


find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Threads REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR} ${ZeroMQ_INCLUDE_DIR})


set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_subdirectory("${PROJECT_SOURCE_DIR}/src")
add_subdirectory("${PROJECT_SOURCE_DIR}/3rd_party")
add_subdirectory("${PROJECT_SOURCE_DIR}/STRUCK")

#message("HEADERS" ${HEADERS})

add_executable(tcomp ${SOURCE} ${HEADERS})
add_definitions(-DSHOW___)
target_link_libraries(tcomp ${OpenCV_LIBS} Threads::Threads ${ZeroMQ_LIBRARY})

