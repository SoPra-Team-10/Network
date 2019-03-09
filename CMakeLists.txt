cmake_minimum_required(VERSION 3.10)
project(NetworkSoPra VERSION 0.0.1 DESCRIPTION "Network for SoPra")

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
set(SOURCES ${CMAKE_SOURCE_DIR}/sopra_network.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Installation via make install
include(GNUInstallDirs)
set(PUBLIC_HEADER sopra_network.h)
set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
        PUBLIC_HEADER ${PUBLIC_HEADER})
install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


add_subdirectory(Tests)