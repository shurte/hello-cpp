cmake_minimum_required(VERSION 4.0)
project(Hello)

include_directories($ENV{SDL_INCLUDE})
link_directories($ENV{SDL_LIB})

include_directories($ENV{GLEW_INCLUDE})
link_directories($ENV{GLEW_LIB})

add_executable(main main.cpp)

target_link_libraries(main SDL2)
target_link_libraries(main glew32)
target_link_libraries(main opengl32)

configure_file($ENV{SDL_BIN}/SDL2.dll ${CMAKE_BINARY_DIR}/SDL2.dll COPYONLY)
configure_file($ENV{GLEW_BIN}/glew32.dll ${CMAKE_BINARY_DIR}/glew32.dll COPYONLY)