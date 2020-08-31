cmake_minimum_required(VERSION 3.14)

project(spdlog_cmake)

set(CMAKE_CXX_STANDARD 14)

# option(FMT_HEADER_ONLY ON)
add_subdirectory(external/fmt EXCLUDE_FROM_ALL)

option(SPDLOG_FMT_EXTERNAL ON)
add_subdirectory(external/spdlog)


add_executable(spdlog_cmake main.cpp)

target_link_libraries(spdlog_cmake fmt::fmt spdlog::spdlog)
