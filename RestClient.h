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

#define ERROR_GETTING_TOKEN -11
#define ERROR_POSTING_DATA -1
#define ERROR_INVALID_TOKEN -2
#define SUCCESS 0

// ----------------------------------------------------------------------
// API DATA STRUCT
// ----------------------------------------------------------------------
/**
 * Defines a structure that holds in memory all the parameters needed to
 * communicate with the Rest API of the application.
 */
struct ApiParams{
    static const std::string HOST;
    static const std::string TOKEN_ENDPOINT;
    static const std::string DEFAULT_CONTENT_TYPE;
    static const std::string DEFAULT_ACCEPT;
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
    // CONSTRUCTOR / DESTRUCTOR -----------------------------------------
    RestClient(std::string, std::string, std::string);
    ~RestClient();

    // CLASS PUBLIC METHODS ---------------------------------------------

    /**
     * Performs an HTTP POST to a given endpoint using the given payload
     * and provided content type.
     * @return
     */
    int post(std::string, std::string, std::string);
private:

    // PRIVATE PROPERTIES -----------------------------------------------
    std::string _userId;
    std::string _userKey;
    std::string _jwtToken;
    std::string _server;

    // PRIVATE METHODS --------------------------------------------------
    std::string buildAuthenticationPayload();
    int fetchJwtToken();

};


#endif //HC_MINER_RESTCLIENT_H
