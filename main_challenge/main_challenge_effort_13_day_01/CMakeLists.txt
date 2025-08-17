cmake_minimum_required(VERSION 4.0)
project(Hello)

include(FetchContent)

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL/
    GIT_TAG release-2.32.8
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(SDL2)

add_executable(main main.cpp)
target_link_libraries(main SDL2)

configure_file(${CMAKE_BINARY_DIR}/_deps/sdl2-build/SDL2.dll ${CMAKE_BINARY_DIR}/SDL2.dll COPYONLY)