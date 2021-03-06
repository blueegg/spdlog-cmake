cmake_minimum_required(VERSION 3.14)

project(spdlog_cmake VERSION 0.1.0 
        LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(fmt
    GIT_REPOSITORY https://hub.fastgit.org/fmtlib/fmt.git
    GIT_TAG 7.1.3
)
FetchContent_MakeAvailable(fmt)

set(SPDLOG_FMT_EXTERNAL ON CACHE INTERNAL "")
FetchContent_Declare(spdlog
    URL https://hub.fastgit.org/gabime/spdlog/archive/v1.8.5.tar.gz
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(json
    GIT_REPOSITORY https://hub.fastgit.org/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
    GIT_TAG v3.9.1
)
FetchContent_MakeAvailable(json)

#
# cpp-httplib with openssl
#
find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    set(HTTPLIB_IS_USING_OPENSSL TRUE)
    message(STATUS "HTTPLIB_IS_USING_OPENSSL")
endif()

set(CPR_FORCE_USE_SYSTEM_CURL ON CACHE INTERNAL "")
set(CPR_BUILD_TESTS OFF CACHE INTERNAL "")
set(CPR_BUILD_TESTS_SSL OFF CACHE INTERNAL "")
set(CPR_USE_SYSTEM_GTEST ON CACHE INTERNAL "")
FetchContent_Declare(cpr 
    GIT_REPOSITORY https://hub.fastgit.org/whoshuu/cpr.git
    GIT_TAG 1.6.0
) 
FetchContent_MakeAvailable(cpr)

add_executable(spdlog_cmake main.cpp)

target_link_libraries(spdlog_cmake PRIVATE spdlog::spdlog_header_only fmt::fmt nlohmann_json::nlohmann_json cpr::cpr)

target_link_libraries(spdlog_cmake PUBLIC
    $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:OpenSSL::SSL>
    $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:OpenSSL::Crypto>)
target_compile_definitions(spdlog_cmake PUBLIC
    $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:CPPHTTPLIB_OPENSSL_SUPPORT>)
