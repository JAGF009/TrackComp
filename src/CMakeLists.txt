set(SOURCE 
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/Rect.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Trajectory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TrackMeas.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pugixml.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/xmlhandler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MOTReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PIXReader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TrackerStruck.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TrackerOpenCV.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TrackerRe3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Factory.cpp
    PARENT_SCOPE)

set(HEADERS
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/Rect.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Trajectory.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TrackMeas.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pugixml.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pugiconfig.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/xmlhandler.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DBReader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MOTReader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PIXReader.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TrackerBasic.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TrackerStruck.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TrackerOpenCV.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TrackerRe3.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Factory.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EnumsConst.hpp
    PARENT_SCOPE)