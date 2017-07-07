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
    int result = -1;
    struct curl_slist* headers;
    if(httpClient){

        // SETUP HEADER PARAMS ----------
        string accept = "Accept: " + contentType;
        string encoding = "charset: utf-8";

        // SETUP URI --------------------
        string uri = this->_server + endpoint;

        // SETUP HEADERS ----------------
        headers = NULL;
        curl_slist_append(headers, accept.c_str());
        curl_slist_append(headers, encoding.c_str());

        // POST DATA
        curl_easy_setopt(httpClient, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(httpClient, CURLOPT_URL, uri.c_str());
        curl_easy_setopt(httpClient, CURLOPT_POST, 1L);
        curl_easy_setopt(httpClient, CURLOPT_POSTFIELDS, payload.c_str());
        curl_easy_setopt(httpClient, CURLOPT_POSTFIELDSIZE, payload.length());
        curl_easy_setopt(httpClient, CURLOPT_VERBOSE, 1L);

        // PERFORM POST OPERATION ------
        ret = curl_easy_perform(httpClient);
        if(ret == CURLE_OK){
            result = 0;
        } // IF ENDS
        else{
            cerr << "CURL ERROR: " << curl_easy_strerror(ret) << endl;
        } // ELSE ENDS

        // CLEANUP ---------------------
        curl_slist_free_all(headers);
        curl_easy_cleanup(httpClient);
        httpClient = NULL;
        payload.clear();
        endpoint.clear();
    } // IF ENDS
    return result;
} // METHOD POST JSON ENDS ----------------------------------------------

// ----------------------------------------------------------------------
// METHOD POST ASYNC
// ----------------------------------------------------------------------
/**
 * Posts a given payload using a background detached thread so that
 * @return 0 when data sent successfully.
 */
int RestClient::postAsync(std::string endpoint, std::string payload, std::string contentType) {
    try{
        thread worker(&RestClient::post, this, endpoint, payload, contentType);
        // Make the thread detached from parent thread so it runs in the background
        // without blocking current execution thread.
        worker.detach();
    } // TRY ENDS
    catch(std::exception e){
        cerr << "CURL ERROR: " << e.what() << endl;
        return -1;
    } // CATCH ENDS
    return 0;
} // METHOD POST ASYNC ENDS ---------------------------------------------

