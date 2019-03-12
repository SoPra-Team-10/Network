cmake_minimum_required(VERSION 3.10)

project(ServerTest)
include_directories(${CMAKE_SOURCE_DIR})

add_executable(${PROJECT_NAME} serverTest.cpp ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LIBS})
