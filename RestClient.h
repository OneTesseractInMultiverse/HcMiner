//
// Created by Pedro Guzmán on 7/2/17.
//

#ifndef HC_MINER_RESTCLIENT_H
#define HC_MINER_RESTCLIENT_H

// IMPORTS -------------------------------------------------------------
#include <string>
#include <curl/curl.h>
#include <iostream>
using namespace std;
// ----------------------------------------------------------------------
// DEFINITIONS
// ----------------------------------------------------------------------

#define SUCCESS 0

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
private:
    std::string _server;
}; // CLASS REST CLIENT ENDS --------------------------------------------


#endif //HC_MINER_RESTCLIENT_H
