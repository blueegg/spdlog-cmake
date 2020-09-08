cmake_minimum_required(VERSION 3.14)

project(spdlog_cmake VERSION 0.1.0 
        LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
set(SPDLOG_FMT_EXTERNAL ON CACHE INTERNAL "")

FetchContent_Declare(fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG origin/master
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(spdlog
    URL https://github.com/gabime/spdlog/archive/v1.8.0.tar.gz
)
FetchContent_MakeAvailable(spdlog)


add_executable(spdlog_cmake main.cpp)

target_link_libraries(spdlog_cmake PRIVATE spdlog::spdlog_header_only fmt::fmt)
