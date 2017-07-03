//
// Created by Pedro Guzmán on 7/2/17.
//

#ifndef HC_MINER_RESTCLIENT_H
#define HC_MINER_RESTCLIENT_H

// IMPORTS -------------------------------------------------------------
#include <string>
#include <curl/curl.h>

// ----------------------------------------------------------------------
// API DATA STRUCT
// ----------------------------------------------------------------------
/**
 * Defines a structure that holds in memory all the parameters needed to
 * communicate with the Rest API of the application.
 */
struct ApiData {
    static const std::string HOST;
    static const std::string TOKEN_ENDPOINT;
    static const std::string PERFDATA_ENDPOINT;
    static const std::string HEADER_CONTENT_TYPE;
    static const std::string HEADER_ACCEPT;
    static const std::string CHARSET;
};

// ----------------------------------------------------------------------
// API DATA STRUCT
// ----------------------------------------------------------------------
/**
 * Represents a REST API Client for Healthcheck API. This class exposes
 * method operations that are invoked as API Web Calls.
 */
class RestClient {


public:
    RestClient(std::string, std::string);
    ~RestClient();
    void send();

private:
    // PRIVATE PROPERTIES -----------------------------------------------
    std::string _userId;
    std::string _userKey;
    std::string _jwtToken;

    void createPerfData();


};


#endif //HC_MINER_RESTCLIENT_H
