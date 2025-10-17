cmake_minimum_required(VERSION 3.31)
project(Hello)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(CPM)
cpmaddpackage("gh:libsdl-org/SDL#release-2.32.8")
cpmaddpackage("gh:Perlmint/glew-cmake#origin/master")
cpmaddpackage("gh:catchorg/Catch2#v3.10.0")

add_subdirectory(hello)

add_executable(main main.cpp)

target_include_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/hello/)
target_link_libraries(main hello)

target_link_libraries(main SDL2)
target_link_libraries(main libglew_shared)
target_link_libraries(main opengl32)

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${SDL2_BINARY_DIR}/SDL2.dll" "${CMAKE_BINARY_DIR}/SDL2.dll"
)

add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${glew_BINARY_DIR}/bin/libglew-shared.dll" "${CMAKE_BINARY_DIR}/libglew-shared.dll"
)

add_executable(test test.cpp)
target_include_directories(test PUBLIC ${CMAKE_SOURCE_DIR}/hello/)
target_link_libraries(test hello)

target_link_libraries(test Catch2WithMain)
