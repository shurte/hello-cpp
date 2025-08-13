add_library(lib src/lib.cpp)
target_include_directories(
    lib 
    PUBLIC 
    inc ${CMAKE_BINARY_DIR}/config/inc/
    )