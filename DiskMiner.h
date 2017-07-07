//
// Created by Pedro Guzman on 7/6/17.
//

#ifndef HC_MINER_DISKMINER_H
#define HC_MINER_DISKMINER_H

/*
 * -----------------------------------------------------------------------
 * INCLUDE HEADERS
 * -----------------------------------------------------------------------
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <unistd.h>
#include "stdlib.h"
#include "sys/types.h"
#include "sys/sysinfo.h"
#include "stdio.h"
#include "RestClient.h"
#include "MiningContext.h"
#include "AbstractMiner.h"
#include "XmlUtil.h"

/*
 * -----------------------------------------------------------------------
 * MACRO DEFINITIONS
 * -----------------------------------------------------------------------
 */
/*
    The /proc/diskstats file displays the I/O statistics
    of block devices. Each line contains the following 14
    fields:
     1 - major number
     2 - minor mumber
     3 - device name
     4 - reads completed successfully
     5 - reads merged
     6 - sectors read
     7 - time spent reading (ms)
     8 - writes completed
     9 - writes merged
    10 - sectors written
    11 - time spent writing (ms)
    12 - I/Os currently in progress
    13 - time spent doing I/Os (ms)
    14 - weighted time spent doing I/Os (ms)
    For more details refer to Documentation/iostats.txt
*/

#define PDS_MAJOR 0
#define PDS_MINOR 1
#define PDS_DEVNAME 2
#define PDS_RXCSUCCESS 3
#define PDS_RXMERGED 4
#define PDS_SECREAD 5
#define PDS_TSREAD 6
#define PDS_WCOMP 7
#define PDS_WMERGED 8
#define PDS_SECSWRIT 9
#define PDS_TSW 10
#define PDS_IOCURRPROG 11
#define PDS_TSDIO 12
#define PDS_WTSDIO 13

/*
 * -----------------------------------------------------------------------
 * CLASS DISK MINER
 * -----------------------------------------------------------------------
 */
class DiskMiner : public AbstractMiner {
public:
    DiskMiner(int, std::string);
    ~DiskMiner();
    void run();
private:
    int _delay;
    std::vector<double>* _captures;
    RestClient* _restClient;
    XmlUtil* _xml;
    int fetchDiskData();
    double getCurrentDiskUsage();
    std::string extractColumnVal(std::string&, int);
}; // CLASS DISK MINER ENDS ----------------------------------------------


#endif //HC_MINER_DISKMINER_H
