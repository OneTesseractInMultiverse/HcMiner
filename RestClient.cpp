//
// Created by Pedro Guzmán on 7/2/17.
//

#include "RestClient.h"

const std::string ApiData::HOST = "http://hcapi.cicc-cr.org";
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


