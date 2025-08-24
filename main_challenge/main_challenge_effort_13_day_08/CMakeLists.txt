cmake_minimum_required(VERSION 4.0)
project(Hello)

include(FetchContent)
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.32.8
)
FetchContent_MakeAvailable(SDL2)

add_executable(main main.cpp)
target_link_libraries(main SDL2)

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_BINARY_DIR}/SDL2.dll ${CMAKE_BINARY_DIR}/SDL2.dll
)