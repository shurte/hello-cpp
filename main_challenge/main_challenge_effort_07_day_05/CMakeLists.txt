cmake_minimum_required(VERSION 3.27)
project(Hello)
file(GLOB SOURCES *.cpp *.hpp)
add_executable(main ${SOURCES})