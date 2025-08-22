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

set(DEBUG_SUFFIX "")
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(DEBUG_SUFFIX "d")
endif()
message("Debug postfix: ${DEBUG_SUFFIX}")

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${SDL2_BUILD_DIR}/SDL2d.dll" "${CMAKE_BINARY_DIR}/SDL2d.dll"
    COMMENT "Copying SDL library."
)
