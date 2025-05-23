cmake_minimum_required(VERSION 4.0)
project(Hello)
file(GLOB SOURCES *.hpp *.cpp)
add_executable(main ${SOURCES})