//
// Created by pedro on 7/4/17.

#include "CpuMiner.h"

// -----------------------------------------------------------------------
// CONSTRUCTOR METHOD
// -----------------------------------------------------------------------
CpuMiner::CpuMiner(int delay, std::string serverName) {
    this->_delay = delay;
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
CpuMiner::~CpuMiner() {
    if(this->_restClient != NULL){
        delete this->_restClient;
    } // IF ENDS
    delete this->_captures;
} // DESTRUCTOR METHOD ENDS ----------------------------------------------

// -----------------------------------------------------------------------
// DESTRUCTOR FETCH CPU DATA
// -----------------------------------------------------------------------
/**
 * Makes system calls to get current CPU usage during several iterations to
 * capture a set of data that the miner will send to the orchestrator.
 * @return 0 if everything completed successfully
 */
int CpuMiner::fetchCpuData() {
    this->_captures->clear();
    for(int i = 0; i < this->_delay*2; ++i){
        try{
            double load[3]; // Allocate memory to store stats response from
                            // system call.
            if(getloadavg(load, 3) != -1){
                double cpuLoad = (load[0]*100)/10; // Normalize metric to %
                this->_captures->push_back(cpuLoad);
            } // IF ENDS
            else{
                std::cerr << "Error getting CPU load percentage "<< std::endl;
            } // ELSE ENDS
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        } // TRY ENDS
        catch(std::exception &e){
            std::cerr << "Error in CpuMiner thread: " << e.what() << std::endl;
        } // CATCH ENDS
    } // FOR ENDS
    return 0;
} // METHOD FETCH DATA ENDS ----------------------------------------------

// -----------------------------------------------------------------------
// METHOD GENERATE XML
// -----------------------------------------------------------------------
/**
 * Generates an XML representation of the data that was captured by the miner
 * TODO Modularize and make this function parametrized
 * @return string with Xml formatted data.
 */
std::string CpuMiner::generateXml() {
    std::ostringstream os;
    if(!this->_captures->empty()){
        os << "<?xml version=\"1.0\" ?>" << std::endl;
        os << "<perf-block>" << std::endl;
        os << "\t<perf-indicator>cpu</perf-indicator>" << std::endl;
        os << "\t<data>" << std::endl;
        for(auto i = this->_captures->begin(); i != this->_captures->end(); ++i){
            os << "\t\t<item>" << *i << "</item>" << std::endl;
        } // FOR ENDS
        os << "\t</data>" << std::endl;
        os << "</perf-block>" << std::endl;
    } // IF ENDS
    return os.str();
} // METHOD GENERATE XML ENDS --------------------------------------------

// -----------------------------------------------------------------------
// METHOD RUN
// -----------------------------------------------------------------------
/**
 * Implements the logic of the miner that runs in a separate thread. This
 * method makes the Miner to get into a continuous loop that executes in
 * a given interval of time
 */
void CpuMiner::run() {
    // Enter a loop while the context is running
    while(this->_context->isRunning()){
        std::cout << "CPU_MINER: capture started..." << std::endl;
        if(!this->fetchCpuData()){
            std::cout << "CPU_MINER: capture completed..." << std::endl;
            std::cout << this->generateXml() << std::endl;
        } // IF ENDS
    } // WHILE ENDS
} // METHOD RUN ENDS
