cmake_minimum_required(VERSION 4.0)
project(Hello)
file(GLOB SOURCE *.cpp *.hpp)
add_executable(main ${SOURCE})