cmake_minimum_required(VERSION 4.0)
project(Hello)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(AddGitSubmodule)

add_git_submodule(external/json)

add_executable(main main.cpp)
target_link_libraries(main nlohmann_json)