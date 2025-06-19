cmake_minimum_required(VERSION 4.0)
project(Hello)
file(GLOB SOURCES *.cpp *.hpp)
add_executable(main ${SOURCES})