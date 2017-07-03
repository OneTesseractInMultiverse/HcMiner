cmake_minimum_required(VERSION 3.7)
project(hc_miner)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp rest_client.cpp rest_client.h RestClient.cpp RestClient.h)
add_executable(hc_miner ${SOURCE_FILES})