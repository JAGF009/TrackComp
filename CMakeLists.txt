cmake_minimum_required(VERSION 3.0.0)

project(TComp)

set(CMAKE_CXX_STANDARD 14)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS} ${EIGEN3_INCLUDE_DIR})


set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_subdirectory("${PROJECT_SOURCE_DIR}/src")
add_subdirectory("${PROJECT_SOURCE_DIR}/3rd_party")
add_subdirectory("${PROJECT_SOURCE_DIR}/STRUCK")

add_executable(tcomp ${SOURCE} ${HEADERS})

target_link_libraries(tcomp ${OpenCV_LIBS})

