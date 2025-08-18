cmake_minimum_required(VERSION 4.0)
project(Hello VERSION 1.0.0)

include(FetchContent)

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.32.8
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
  glew-cmake
  GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
  GIT_TAG        origin/master
)
FetchContent_MakeAvailable(glew-cmake)
# add_subdirectory(${glew_SOURCE_DIR} ${glew_BINARY_DIR} EXCLUDE_FROM_ALL)
# add_subdirectory(${glew_SOURCE_DIR})

add_executable(main main.cpp)
target_link_libraries(main SDL2)
target_link_libraries(main libglew_static)
target_link_libraries(main opengl32)

configure_file(${CMAKE_BINARY_DIR}/_deps/sdl2-build/SDL2.dll ${CMAKE_BINARY_DIR}/SDL2.dll COPYONLY)
configure_file(${CMAKE_BINARY_DIR}/_deps/glew-cmake-build/bin/libglew-shared.dll ${CMAKE_BINARY_DIR}/libglew-shared.dll COPYONLY)