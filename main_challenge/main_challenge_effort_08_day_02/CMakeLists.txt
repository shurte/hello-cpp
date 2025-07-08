cmake_minimum_required(VERSION 4.0)
project(Hello)
file(GLOB SOURCES *.cpp *.hpp)

include_directories($ENV{SDL_HOME}include/SDL2)
link_directories($ENV{SDL_HOME}lib)

include_directories($ENV{SDL_TTF_HOME}include)
link_directories($ENV{SDL_TTF_HOME}lib)

add_executable(main ${SOURCES})

target_link_libraries(main SDL2)
target_link_libraries(main SDL2_ttf)

configure_file($ENV{SDL_HOME}bin/SDL2.dll ${CMAKE_BINARY_DIR}/SDL2.dll COPYONLY)
configure_file($ENV{SDL_TTF_HOME}bin/SDL2_ttf.dll ${CMAKE_BINARY_DIR}/SDL2_ttf.dll COPYONLY)