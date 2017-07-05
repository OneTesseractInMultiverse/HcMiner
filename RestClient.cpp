//
// Created by Pedro Guzmán on 7/2/17.
//

#include "RestClient.h"

// ----------------------------------------------------------------------
// CONSTRUCTOR
// ----------------------------------------------------------------------
/**
 * Constructor of RestClient. Returns a pointer to a new instance of Rest
 * Client class.
 * @param userId The user identifier to be user for authentication
 * @param userKey The user secret to be used for authentication
 */
RestClient::RestClient(std::string server) {
    this->_server = server;
} // CONSTRUCTOR METHOD ENDS --------------------------------------------

// ----------------------------------------------------------------------
// DESTRUCTOR
// ----------------------------------------------------------------------
/**
 * Releases resources and does cleanup of the resources used by the Rest
 * Client.
 */
RestClient::~RestClient() {

} // DESTRUCTOR ENDS ----------------------------------------------------

// ----------------------------------------------------------------------
// METHOD POST
// ----------------------------------------------------------------------
/**
 * Sends an HTTP POST request to a given endpoint with the given payload.
 * @param endpoint The uri of the endpoint that will receive the data
 * @param payload Payload that will be sent to the endpoint using HTTP POST
 * @param contentType The associated MIME type that will be used on the request
 * @return 0 if operation completed successfully
 */
int RestClient::post(std::string endpoint, std::string payload, std::string contentType){
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
        payload.clear();
        endpoint.clear();
    } // IF ENDS
    return SUCCESS;
} // METHOD POST JSON ENDS ----------------------------------------------

