// ----------------------------------------------------------------
// HC MINER
// ----------------------------------------------------------------

/**
 * Author: Pedro Guzman (pguzmanb498@ulacit.ed.cr)
 * This software is the my solution for workshop 1 of Web Services
 * course at ULACIT. All rights reserved. Unauthorized use of this
 * work is completely prohibited.
 */

#include <iostream>
#include <thread>
#include "CpuMiner.h"
#include "MemMiner.h"
#include "NetMiner.h"
#include "DiskMiner.h"

int main() {

    std::cout << " ======================================================== " << std::endl;
    std::cout << "Copyright (R) 2017 Pedro Guzman. All rights reserved." << std::endl;
    std::cout << "Universidad Latinoamericana de Ciencia y Tecnologia" << std::endl;
    std::cout << "Course: Web Services" << std::endl;
    std::cout << " ======================================================== " << std::endl;
    std::cout << "Running HcMiner..." << std::endl;


    std::string apiServer = "http://api.miner.com";

    // First we create the shared MiningContext
    MiningContext * context = new MiningContext();
    context->init();

    // CPU AGENT ---------------------------------------------------
    CpuMiner * cpuMiner = new CpuMiner(12, apiServer);
    cpuMiner->setContext(context);
    std::thread cpuAgent = cpuMiner->spawn();

    // MEMORY AGENT ------------------------------------------------
    MemMiner * memMiner = new MemMiner(20, apiServer);
    memMiner->setContext(context);
    std::thread memAgent = memMiner->spawn();

    // NETWORK AGENT -----------------------------------------------
    NetMiner * netMiner = new NetMiner(8, apiServer);
    netMiner->setContext(context);
    std::thread netAgent = netMiner->spawn();

    // DISK AGENT --------------------------------------------------
    DiskMiner * diskMiner = new DiskMiner(10, apiServer);
    diskMiner->setContext(context);
    std::thread diskAgent = diskMiner->spawn();

    // JOIN AGENT THREADS ------------------------------------------
    cpuAgent.join();
    memAgent.join();
    netAgent.join();
    diskAgent.join();

    // Stop the mining context
    context->stop();

    // Return memory allocations on heap segment to the OS.
    delete context;
    delete cpuMiner;
    delete memMiner;
    delete netMiner;
    delete diskMiner;

    // Program exits with success status code
    return 0;
} // MAIN FUNCTION ENDS ---------------------------------------------