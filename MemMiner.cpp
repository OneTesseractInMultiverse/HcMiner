//
// Created by Pedro Guzman on 7/5/17.
//

#include "MemMiner.h"

// -----------------------------------------------------------------------
// CONSTRUCTOR METHOD
// -----------------------------------------------------------------------
MemMiner::MemMiner(int delay, std::string serverName) {
    this->_delay = delay;
    this->_xml = new XmlUtil();
    this->_restClient = new RestClient(serverName);
    this->_captures = new std::vector<double>();
} // CONSTRUCTOR METHOD ENDS ---------------------------------------------

// -----------------------------------------------------------------------
// DESTRUCTOR METHOD
// -----------------------------------------------------------------------
/**
 * This is the destructor of the class. Releases all the resources used by
 * the class.
 */
MemMiner::~MemMiner() {
    if(this->_restClient != NULL){
        delete this->_restClient;
    } // IF ENDS
    delete this->_captures;
    delete this->_xml;
} // DESTRUCTOR METHOD ENDS ----------------------------------------------

// -----------------------------------------------------------------------
// DESTRUCTOR FETCH MEM DATA
// -----------------------------------------------------------------------
/**
 * Makes system calls to get current CPU usage during several iterations to
 * capture a set of data that the miner will send to the orchestrator.
 * @return 0 if everything completed successfully
 */
int MemMiner::fetchMemData() {
    this->_captures->clear();
    const double mb = 1024 * 1024;
    for(int i = 0; i < this->_delay*2; ++i){
        try{
            struct sysinfo si;
            if(!sysinfo(&si)){
                auto memUsage = 100.0 - (((si.freeram / mb) * 100) / (si.totalram / mb));
                this->_captures->push_back(memUsage);
            } // IF ENDS
            else{
                std::cerr << "Error getting mem performance data" << std::endl;
            } // ELSE ENDS
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        } // TRY ENDS
        catch(std::exception &e){
            std::cerr << "Error in MemMiner thread: " << e.what() << std::endl;
        } // CATCH ENDS
    } // FOR ENDS
    return 0;
} // METHOD FETCH DATA ENDS ----------------------------------------------

// -----------------------------------------------------------------------
// METHOD RUN
// -----------------------------------------------------------------------
/**
 * Implements the logic of the miner that runs in a separate thread. This
 * method makes the Miner to get into a continuous loop that executes in
 * a given interval of time
 */
void MemMiner::run() {
    // Enter a loop while the context is running
    while(this->_context->isRunning()){
        std::cout << "MEM_MINER: capture started..." << std::endl;
        if(!this->fetchMemData()){
            this->_restClient->postAsync(
                    "/api/v1/mem",
                    this->_xml->createXml("mem", this->_captures),
                    "application/xml"
            );
            std::cout << "MEM_MINER: capture completed..." << std::endl;
            std::cout << this->_xml->createXml("mem", this->_captures) << std::endl;
        } // IF ENDS
    } // WHILE ENDS
} // METHOD RUN ENDS