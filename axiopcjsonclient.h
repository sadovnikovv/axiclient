/* 
 * File:   axiopcjsonclient.h
 * Author: v.sadovnikov
 *
 * Created on 26 октября 2017 г., 8:20
 */

#ifndef AXIOPCJSONCLIENT_H
#define AXIOPCJSONCLIENT_H

#include "json.hpp"

#include <curl/curl.h>
#include <map>
#include <iostream>

using nlohmann::json;
using namespace std;

class AxiOpcJsonClient {
public:
    AxiOpcJsonClient(const std::string &url);
    ~AxiOpcJsonClient();
    void SendRPCMessage(const std::string &message, std::string &result);
    void SetUrl(const std::string &url);
    void SetTimeout(long timeout);
    void AddHeader(const std::string &attr, const std::string &val);
    void RemoveHeader(const std::string &attr);
    void setTarget(char* target) { this->target = target; }
private:
    std::map<std::string, std::string> headers;
    std::string url;
    long timeout;
    CURL *curl;
    //string targetHost;
    //unsigned targetPort;
    char *target;
   
    
};


#endif /* AXIOPCJSONCLIENT_H */

