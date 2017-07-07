//
// Created by pedro on 7/6/17.
//

#include "DiskMiner.h"

// -----------------------------------------------------------------------
// CONSTRUCTOR METHOD
// -----------------------------------------------------------------------
/**
 * Allocates memory for an instance of DiskMiner and return a pointer to its
 * location on the heap;
 * @param delay
 * @param serverName
 */
DiskMiner::DiskMiner(int delay, std::string serverName) {
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
DiskMiner::~DiskMiner() {
    if(this->_restClient != NULL){
        delete this->_restClient;
    } // IF ENDS
    delete this->_captures;
    delete this->_xml;
} // DESTRUCTOR METHOD ENDS ----------------------------------------------

// -----------------------------------------------------------------------
// METHOD EXTRACT COLUMN VAL
// -----------------------------------------------------------------------
/**
 * Given a space separated string, it extract the value in the given
 * position
 * @param s the space separated string
 * @param position - of the element to get
 * @return a string value in a given position
 */
std::string DiskMiner::extractColumnVal(std::string & s, int position) {
    std:: string result("");
    std::istringstream iss(s);
    int i = 0;
    do {
        std::string sub;
        iss >> sub;
        if( i == position){
            result = sub;
            // We exit the loop once thje value is found
            break;
        } // IF ENDS
        i++;
    } while (iss);
    return result;
} // METHOD EXTRACT COLUMN VALUE END  ------------------------------------

// -----------------------------------------------------------------------
// METHOD GET CURRENT NET USAGE
// -----------------------------------------------------------------------
/**
 * This only works in Linux since parsing (/proc) file system is not portable
 * to other operating systems. This method fetches Disk utilization based
 * on the amount of time spent doing I/O operations during a given timespan.
 * @return Current miliseconds spent doing I/O
 */
double DiskMiner::getCurrentDiskUsage() {
    FILE *fp = fopen("/proc/diskstats", "r");
    char buf[200];
    bool devFound = false;
    long tsdio = 0;
    while (fgets(buf, 200, fp) && !devFound) {
        std:: string line(buf);
        if(extractColumnVal(line, PDS_DEVNAME) == "sda"){
            tsdio = atol(extractColumnVal(line, PDS_TSDIO).c_str());
            devFound = true;
        } // IF ENDS
    } // WHILE ENDSS
    fclose(fp);
    return tsdio;
} // METHOD GET CURRENT NET USAGE ENDS -----------------------------------

// -----------------------------------------------------------------------
// DESTRUCTOR FETCH MEM DATA
// -----------------------------------------------------------------------
/**
 * Makes system calls to get current Net usage during several iterations to
 * capture a set of data that the miner will send to the orchestrator.
 * @return 0 if everything completed successfully
 */
int DiskMiner::fetchDiskData() {
    this->_captures->clear();
    for(int i = 0; i < this->_delay; ++i){
        try{
            double initialIO = this->getCurrentDiskUsage();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            double deltaIO = this->getCurrentDiskUsage();
            this->_captures->push_back(std::abs(initialIO - deltaIO));
        } // TRY ENDS
        catch(std::exception &e){
            std::cerr << "Error in DiskMiner thread: " << e.what() << std::endl;
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
void DiskMiner::run() {
    // Enter a loop while the context is running
    while(this->_context->isRunning()){
        std::cout << "DISK_MINER: capture started..." << std::endl;
        if(!this->fetchDiskData()){
            std::cout << "DISK_MINER: capture completed..." << std::endl;
            std::cout << this->_xml->createXml("disk", this->_captures) << std::endl;
        } // IF ENDS
    } // WHILE ENDS
} // METHOD RUN ENDS