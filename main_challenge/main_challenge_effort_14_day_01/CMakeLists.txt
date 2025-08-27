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

add_executable(test test.cpp)
target_include_directories(test PUBLIC "./")
target_link_libraries(test Catch2WithMain)