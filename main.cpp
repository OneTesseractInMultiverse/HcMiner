#include <iostream>
#include <thread>
#include "CpuMiner.h"

int main() {
    std::cout << "Running HcMiner..." << std::endl;

    // First we create the shared MiningContext
    MiningContext* context = new MiningContext();
    context->init();

    // CPU AGENT
    CpuMiner* cpuMiner = new CpuMiner(2, "http://api.miner.com");
    cpuMiner->setContext(context);
    std::thread cpuAgent = cpuMiner->spawn();
    cpuAgent.join();

    // Stop the mining context
    context->stop();

    // Return memory allocations on heap segment to the OS.
    delete context;
    delete cpuMiner;
    return 0;
}