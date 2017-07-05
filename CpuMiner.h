//
// Created by pedro on 7/4/17.
//

#ifndef HC_MINER_CPUMINER_H
#define HC_MINER_CPUMINER_H

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
#include "stdio.h"
#include "RestClient.h"
#include "MiningContext.h"
#include "AbstractMiner.h"

// =======================================================================
// CLASS ABSTRACT MINER
// =======================================================================

class CpuMiner : public AbstractMiner{

public:
    CpuMiner(int, std::string);
    ~CpuMiner();
    void run();
private:
    int _delay;
    std::vector<double>* _captures;
    RestClient* _restClient;
    int fetchCpuData();
    std::string generateXml();
};


#endif //HC_MINER_CPUMINER_H
