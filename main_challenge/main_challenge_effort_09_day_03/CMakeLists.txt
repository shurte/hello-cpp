cmake_minimum_required(VERSION 4.0)
project(Hello)

include_directories($ENV{SDL_HOME}/include)
include_directories($ENV{GLEW_HOME}/include)

link_directories($ENV{SDL_HOME}/lib)
link_directories($ENV{GLEW_HOME}/lib/Release/x64)

add_executable(main main.cpp)

target_link_libraries(main SDL2)
target_link_libraries(main glew32)
target_link_libraries(main opengl32)

configure_file($ENV{SDL_HOME}/bin/SDL2.dll ${CMAKE_BINARY_DIR}/SDL2.dll COPYONLY)
configure_file($ENV{GLEW_HOME}/bin/Release/x64/glew32.dll ${CMAKE_BINARY_DIR}/glew32.dll COPYONLY)