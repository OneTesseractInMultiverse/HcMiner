//
// Created by Pedro Guzman on 7/2/17.
//

#ifndef HC_MINER_RESTCLIENT_H
#define HC_MINER_RESTCLIENT_H

// IMPORTS -------------------------------------------------------------

#include <thread>
#include <string>
#include <iostream>
#include <curl/curl.h>
using namespace std;

// ----------------------------------------------------------------------
// API DATA STRUCT
// ----------------------------------------------------------------------
/**
 * Represents a REST API Client for Healthcheck API. This class exposes
 * method operations that are invoked as API Web Calls.
 */
class RestClient {
public:
    RestClient(std::string);
    ~RestClient();
    int post(std::string, std::string, std::string);
    int postAsync(std::string, std::string, std::string);
private:
    std::string _server;
}; // CLASS REST CLIENT ENDS --------------------------------------------

#endif //HC_MINER_RESTCLIENT_H
