
# message("HELLO FROM 3rd PARTY")

set(SOURCE 
    ${SOURCE}
    ${CMAKE_CURRENT_SOURCE_DIR}/ConfigFile.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/formated_string.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filesystem.cpp
    PARENT_SCOPE)

# message("THIRD PARTY SOURCE " ${SOURCE})

set(HEADERS
    ${HEADERS}
    ${CMAKE_CURRENT_SOURCE_DIR}/ConfigFile.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/formated_string.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filesystem.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/subprocess.hpp
    PARENT_SCOPE)
