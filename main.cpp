#include <iostream>
#include <thread>
#include "CpuMiner.h"
#include "MemMiner.h"

int main() {
    std::cout << "Running HcMiner..." << std::endl;
    std::string apiServer = "http://api.miner.com";

    // First we create the shared MiningContext
    MiningContext* context = new MiningContext();
    context->init();

    // CPU AGENT ---------------------------------------------------
    CpuMiner* cpuMiner = new CpuMiner(2, apiServer);
    cpuMiner->setContext(context);
    std::thread cpuAgent = cpuMiner->spawn();


    // MEMORY AGENT ------------------------------------------------
    MemMiner* memMiner = new MemMiner(2, apiServer);
    memMiner->setContext(context);
    std::thread memAgent = memMiner->spawn();

    // JOIN AGENT THREADS ------------------------------------------
    cpuAgent.join();
    memAgent.join();

    // Stop the mining context
    context->stop();

    // Return memory allocations on heap segment to the OS.
    delete context;
    delete cpuMiner;
    delete memMiner;
    return 0;
}