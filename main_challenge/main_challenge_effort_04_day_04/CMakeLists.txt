cmake_minimum_required(VERSION 4.0)
project(Hello)
file(GLOB SOURCES *.hpp *.cpp)
# here "SOURCES" is a name for a CMake variable 
# it should be in capital letters because there are some issues if there are small and capital letters in the variable name 
add_executable(main ${SOURCES})
# here "${SOURCES}" is just calling for the variable value