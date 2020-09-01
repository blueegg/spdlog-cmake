cmake_minimum_required(VERSION 3.14)

project(spdlog_cmake CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(spdlog_cmake main.cpp)

target_include_directories(spdlog_cmake PRIVATE external)
