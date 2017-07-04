cmake_minimum_required(VERSION 3.7)
project(hc_miner)

set(CMAKE_CXX_STANDARD 11)
find_package(curl REQUIRED)
set(GCC_COVERAGE_LINK_FLAGS "-lcurl")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
set(SOURCE_FILES main.cpp RestClient.cpp RestClient.h)
add_executable(hc_miner ${SOURCE_FILES})