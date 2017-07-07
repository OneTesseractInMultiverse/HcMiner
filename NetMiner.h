//
// Created by Pedro Guzman on 7/5/17.
//

#ifndef HC_MINER_NETMINER_H
#define HC_MINER_NETMINER_H

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
// CLASS NET MINER
// =======================================================================
class NetMiner : public AbstractMiner {
public:
    NetMiner(int, std::string);
    ~NetMiner();
    void run();
private:
    int _delay;
    std::vector<double>* _captures;
    RestClient* _restClient;
    XmlUtil* _xml;
    int fetchNetData();
    double getCurrentNetUsage();
};


#endif //HC_MINER_NETMINER_H
