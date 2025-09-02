cmake_minimum_required(VERSION 4.0)
project(Hello)

include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2
    GIT_TAG v3.10.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Catch2)

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.32.8
)
FetchContent_MakeAvailable(SDL2)

add_executable(main main.cpp)
target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(main SDL2)

add_executable(test test.cpp)
target_include_directories(test PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(test Catch2WithMain)

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${SDL2_BINARY_DIR}/SDL2.dll" "${CMAKE_BINARY_DIR}/SDL2.dll"
)