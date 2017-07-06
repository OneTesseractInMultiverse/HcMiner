//
// Created by pedro on 7/5/17.
//

#ifndef HC_MINER_MEMMINER_H
#define HC_MINER_MEMMINER_H

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
#include <unistd.h>
#include "stdlib.h"
#include "sys/types.h"
#include "sys/sysinfo.h"
#include "stdio.h"
#include "RestClient.h"
#include "MiningContext.h"
#include "AbstractMiner.h"
#include "XmlUtil.h"

// =======================================================================
// CLASS MEM MINER
// =======================================================================
class MemMiner : public AbstractMiner {

public:
    MemMiner(int, std::string);
    ~MemMiner();
    void run();
private:
    int _delay;
    std::vector<double>* _captures;
    RestClient* _restClient;
    XmlUtil* _xml;
    int fetchMemData();
}; // CLASS MEM MINER ENDS -----------------------------------------------

#endif //HC_MINER_MEMMINER_H
