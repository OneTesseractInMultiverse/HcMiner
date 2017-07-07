//
// Created by Pedro Guzman on 7/5/17.
//

#include "NetMiner.h"

// -----------------------------------------------------------------------
// CONSTRUCTOR METHOD
// -----------------------------------------------------------------------
/**
 * Allocates memory for an instance of NetMiner and return a pointer to its
 * location on the heap;
 * @param delay
 * @param serverName
 */
NetMiner::NetMiner(int delay, std::string serverName) {
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
 * the class. Prevents creation of memory leaks.
 */
NetMiner::~NetMiner() {
    if(this->_restClient != NULL){
        delete this->_restClient;
    } // IF ENDS
    delete this->_captures;
    delete this->_xml;
} // DESTRUCTOR METHOD ENDS ----------------------------------------------

// -----------------------------------------------------------------------
// METHOD GET CURRENT NET USAGE
// -----------------------------------------------------------------------
/**
 * This only works in Linux since parsing (/proc) file system is not portable
 * @return Current received bytes (RxBytes) in Mb used as a delta to
 *         determine Mb/s.
 */
double NetMiner::getCurrentNetUsage() {
    FILE *fp = fopen("/proc/net/dev", "r");
    char buffer[200];
    char interface[20];
    unsigned long int r_bytes, t_bytes, r_packets, t_packets;
    double usage = 0.0;
    double megabyte = 1024; // 1Mb = 1024 Bytes

    // Tx: Transmit | Rx: Receive
    // skip first two lines which are only headers
    for (int i = 0; i < 2; i++) {
        fgets(buffer, 200, fp);
    } // FOR ENDS

    // Read all interface statistics and exit when main interface found.
    while (fgets(buffer, 200, fp)) {
        sscanf(buffer, "%[^:]: %lu %lu %*lu %*lu %*lu %*lu %*lu %*lu %lu %lu",
               interface, &r_bytes, &r_packets, &t_bytes, &t_packets);
        std::string iface(interface);
        usage +=  (double)r_bytes;
    } // WHILE ENDS
    fclose(fp);
    return usage;
} // METHOD GET CURRENT NET USAGE ENDS -----------------------------------

// -----------------------------------------------------------------------
// DESTRUCTOR FETCH MEM DATA
// -----------------------------------------------------------------------
/**
 * Makes system calls to get current Net usage during several iterations to
 * capture a set of data that the miner will send to the orchestrator.
 * @return 0 if everything completed successfully
 */
int NetMiner::fetchNetData() {
    this->_captures->clear();
    const double mb = 1024 * 1024;
    for(int i = 0; i < this->_delay; ++i){
        try{
            double initialRx = this->getCurrentNetUsage();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            double deltaRx = this->getCurrentNetUsage();
            this->_captures->push_back((deltaRx-initialRx));
        } // TRY ENDS
        catch(std::exception &e){
            std::cerr << "Error in MemMiner thread: " << e.what() << std::endl;
            return 1;
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
void NetMiner::run() {
    // Enter a loop while the context is running
    while(this->_context->isRunning()){
        std::cout << "NET_MINER: capture started..." << std::endl;
        if(!this->fetchNetData()){
            this->_restClient->postAsync(
                    "/api/v1/net",
                    this->_xml->createXml("net", this->_captures),
                    "application/xml"
            );
            std::cout << "NET_MINER: capture completed..." << std::endl;
            std::cout << this->_xml->createXml("net", this->_captures) << std::endl;
        } // IF ENDS
    } // WHILE ENDS
} // METHOD RUN ENDS