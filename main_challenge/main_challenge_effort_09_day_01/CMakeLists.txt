cmake_minimum_required(VERSION 4.0)
project(Hello)
file(GLOB SOURCES *.cpp *.hpp)

include_directories(c:/_development/sandbox/cpp/libs/SDL2-2.32.8/x86_64-w64-mingw32/include)
include_directories(c:/_development/sandbox/cpp/libs/glew-2.1.0/include)
link_directories(c:/_development/sandbox/cpp/libs/SDL2-2.32.8/x86_64-w64-mingw32/lib)
link_directories(c:/_development/sandbox/cpp/libs/glew-2.1.0/lib/Release/x64)
link_directories(c:/_programs/msys64/ucrt64/lib)

add_executable(main ${SOURCES})

target_link_libraries(main SDL2)
target_link_libraries(main glew32)
target_link_libraries(main opengl32)

configure_file(c:/_development/sandbox/cpp/libs/SDL2-2.32.8/x86_64-w64-mingw32/bin/SDL2.dll ${CMAKE_CURRENT_BINARY_DIR}/SDL2.dll COPYONLY)
configure_file(c:/_development/sandbox/cpp/libs/glew-2.1.0/bin/Release/x64/glew32.dll ${CMAKE_CURRENT_BINARY_DIR}/glew32.dll COPYONLY)