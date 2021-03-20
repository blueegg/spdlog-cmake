cmake_minimum_required(VERSION 3.14)

project(spdlog_cmake VERSION 0.1.0 
        LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

FetchContent_Declare(fmt
    GIT_REPOSITORY https://hub.fastgit.org/fmtlib/fmt.git
    GIT_TAG 7.1.3
)
FetchContent_MakeAvailable(fmt)

set(SPDLOG_FMT_EXTERNAL ON CACHE INTERNAL "")
FetchContent_Declare(spdlog
    URL https://hub.fastgit.org/gabime/spdlog/archive/v1.8.2.tar.gz
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(json
    GIT_REPOSITORY https://hub.fastgit.org/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
    GIT_TAG v3.9.1
)
FetchContent_MakeAvailable(json)

set(CPR_FORCE_USE_SYSTEM_CURL ON CACHE INTERNAL "")
FetchContent_Declare(cpr 
    GIT_REPOSITORY https://hub.fastgit.org/whoshuu/cpr.git
    GIT_TAG 1.6.0
) 
FetchContent_MakeAvailable(cpr)

add_executable(spdlog_cmake main.cpp)

target_link_libraries(spdlog_cmake PRIVATE spdlog::spdlog_header_only fmt::fmt nlohmann_json::nlohmann_json cpr::cpr)
