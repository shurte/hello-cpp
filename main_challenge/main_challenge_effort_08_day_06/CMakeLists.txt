cmake_minimum_required(VERSION 3.29)
project(Hello)
file(GLOB SOURCES *.cpp *.hpp)

include_directories($ENV{SDL_HOME}/include/SDL2)
link_directories($ENV{SDL_HOME}/lib/)

add_executable(main ${SOURCES})
target_link_libraries(main SDL2)

configure_file($ENV{SDL_HOME}/bin/SDL2.dll ${CMAKE_CURRENT_BINARY_DIR}/SDL2.dll COPYONLY)