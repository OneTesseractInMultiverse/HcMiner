cmake_minimum_required(VERSION 3.7)
project(hc_miner)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lcurl -pthread")
link_directories(/usr/lib/x86_64-linux-gnu/)

set(SOURCE_FILES main.cpp RestClient.cpp RestClient.h AbstractMiner.h MiningContext.cpp MiningContext.h CpuMiner.cpp CpuMiner.h)
add_executable(hc_miner ${SOURCE_FILES})