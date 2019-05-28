cmake_minimum_required(VERSION 3.10)

# Build options
set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
endif ()

# Building
project(SopraNetwork VERSION 0.0.1 DESCRIPTION "Network for SoPra")

set(SOURCES
        ${CMAKE_SOURCE_DIR}/src/Server/WebSocketServer.cpp
        ${CMAKE_SOURCE_DIR}/src/Server/Connection.cpp
        ${CMAKE_SOURCE_DIR}/src/Client/WebSocketClient.cpp)

set(LIBS websockets pthread)

include_directories(${CMAKE_SOURCE_DIR})
add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS})

# Installation via make install
include(GNUInstallDirs)
set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER
        "src/Server/WebSocketServer.hpp;src/Server/Connection.hpp;src/Listener.hpp;src/Client/WebSocketClient.hpp")
install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/SopraNetwork)

add_subdirectory(Tests)
add_subdirectory(Examples)