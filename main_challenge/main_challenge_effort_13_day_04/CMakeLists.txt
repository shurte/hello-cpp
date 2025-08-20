cmake_minimum_required(VERSION 4.0)
project(Hello)

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
    GIT_TAG origin/master
)
FetchContent_MakeAvailable(glew-cmake)

add_executable(main main.cpp)
target_link_libraries(main SDL2)
target_link_libraries(main libglew_shared)
target_link_libraries(main opengl32)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${SDL2_BINARY_DIR}/SDL2d.dll" "${CMAKE_BINARY_DIR}/SDL2d.dll"
    )

    add_custom_command(
        TARGET main POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy "${glew_BINARY_DIR}/bin/libglew-sharedd.dll" "${CMAKE_BINARY_DIR}/libglew-sharedd.dll"
        COMMENT "Copy libglew-shared.dll"
    )
else()
    add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${SDL2_BINARY_DIR}/SDL2.dll" "${CMAKE_BINARY_DIR}/SDL2.dll"
    )

    add_custom_command(
        TARGET main POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy "${glew_BINARY_DIR}/bin/libglew-shared.dll" "${CMAKE_BINARY_DIR}/libglew-shared.dll"
        COMMENT "Copy libglew-shared.dll"
    )
endif()