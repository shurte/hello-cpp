include_directories(inc)
add_library(lib src/lib.cpp)
target_include_directories(lib PUBLIC inc)