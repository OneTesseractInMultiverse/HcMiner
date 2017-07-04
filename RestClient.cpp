//
// Created by Pedro Guzmán on 7/2/17.
//

#include "RestClient.h"

const std::string ApiData::HOST = "http://localhost:8080";
const std::string ApiData::TOKEN_ENDPOINT = "/api/v1/auth";
const std::string ApiData::PERFDATA_ENDPOINT = "/api/v1/perfdata";
const std::string ApiData::HEADER_CONTENT_TYPE = "application/json";
const std::string ApiData::HEADER_ACCEPT = "application/json";
const std::string ApiData::CHARSET = "utf-8";

// ----------------------------------------------------------------------
// CONSTRUCTOR
// ----------------------------------------------------------------------
/**
 * Constructor of RestClient. Returns a pointer to a new instance of Rest
 * Client class.
 * @param userId The user identifier to be user for authentication
 * @param userKey The user secret to be used for authentication
 */
RestClient::RestClient(std::string userId, std::string userKey) {
    this->_userId = userId;
    this->_userKey = userKey;
} // CONSTRUCTOR METHOD ENDS --------------------------------------------

// ----------------------------------------------------------------------
// DESTRUCTOR
// ----------------------------------------------------------------------
/**
 * Releases resources and does cleanup of the resources used by the Rest
 * Client.
 */
RestClient::~RestClient() {
    this->_userKey.clear();
    this->_userKey.clear();
    this->_jwtToken.clear();
} // DESTRUCTOR ENDS ----------------------------------------------------

/**
 * Create JSON payload to be used for authentication against the authentication
 * endpoint
 * @return Json payload for authentication
 */
std::string RestClient::buildAuthenticationPayload() {
    std::string data = "{\"username\":\"" + this->_userId + "\",\"password\":\"" + this->_userKey + "\"}";
    return data;
} // METHOD BUILD AUTHENTICATION PAYLOAD ENDS ---------------------------

/**
 * https://stackoverflow.com/questions/8251325/how-do-i-post-a-buffer-of-json-using-libcurl
 * https://stackoverflow.com/questions/23052900/json-request-using-curl-in-c
 * https://cmake.org/cmake-tutorial/
 * @return
 */
int RestClient::fetchJwtToken() {
    CURL* httpClient;
    CURLcode ret;
    struct curl_slist* headers;
    if(!this->_userId.empty() && !this->_jwtToken.empty()){
        httpClient = curl_easy_init();
        std::string data = this->buildAuthenticationPayload();
        std::string uri = ApiData::HOST+ApiData::TOKEN_ENDPOINT;
        if(httpClient){
            headers = NULL;
            headers = curl_slist_append(headers, "Content-Type: application/json");
            curl_easy_setopt(httpClient, CURLOPT_URL, uri.c_str());
            curl_easy_setopt(httpClient, CURLOPT_POST, 1L);
            curl_easy_setopt(httpClient, CURLOPT_POSTFIELDS, data.c_str());
            curl_easy_setopt(httpClient, CURLOPT_POSTFIELDSIZE, data.length());
            ret = curl_easy_perform(httpClient);
            std::cout << ret << std::endl;
            curl_easy_cleanup(httpClient);
            httpClient = NULL;
            data.clear();
            uri.clear();
        } // IF ENDS
    } // iF ENDS
    return SUCCESS;
} // METHOD FETCH JWT TOKEN ENDS ----------------------------------------


/**
 *
 * @param endpoint
 * @param json
 * @return
 */
int RestClient::post(std::string endpoint, std::string payload, std::string contentType){

    if(this->fetchJwtToken() == SUCCESS){
        CURL* httpClient = curl_easy_init();
        CURLcode ret;
        struct curl_slist* headers;
        if(httpClient){

            // SETUP HEADERS ----------------
            headers = NULL;
            headers = curl_slist_append(headers, contentType.c_str());

            curl_easy_setopt(httpClient, CURLOPT_URL, endpoint.c_str());
            curl_easy_setopt(httpClient, CURLOPT_POST, 1L);
            curl_easy_setopt(httpClient, CURLOPT_POSTFIELDS, payload.c_str());
            curl_easy_setopt(httpClient, CURLOPT_POSTFIELDSIZE, payload.length());
            curl_easy_setopt(httpClient, CURLOPT_VERBOSE, 1L);

            // PERFORM POST OPERATION ------
            ret = curl_easy_perform(httpClient);
            std::cout << ret << std::endl;

            // CLEANUP ---------------------
            curl_easy_cleanup(httpClient);
            httpClient = NULL;
            data.clear();
            uri.clear();
        } // IF ENDS
    } // IF ENDS
    return SUCCESS;
} // METHOD POST JSON ENDS ----------------------------------------------

