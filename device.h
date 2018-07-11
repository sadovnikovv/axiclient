/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   device.h
 * Author: v.sadovnikov
 *
 * Created on 13 ноября 2017 г., 13:46
 */

#ifndef DEVICE_H
#define DEVICE_H

#include <list>



class Device{
public:
    Device(std::string serial);
    ~Device();
    // set host and port
    void setTargetHost(std::string host){ this->targetHost = new std::string(host);}
    void setTargetPort(unsigned port) {this->targetPort = port;}

    std::string getTargetHost() {return targetHost;}
    int getTargetPort() {return targetPort;}
    
    // get queue
    std::list<json> getMessageQueue() {return messageQueue; }
    
    // get serial
    std::string getSerialNumber() {return serialNumber; }
    
    
// device can connect
    bool connect();
    // device can disconnect
    bool disconnect();
    // device can send
    void send(json object);
    
    //device can recieve
    json recv();
    
    // device can send and recieve
    bool deviceSendAndRecv();

    // device main cycle
    
    // FUTURE device THread run()
    
private:
    std::string targetHost;
    unsigned targetPort;
    int socket;
    std::string *serialNumber;
    std::list<json> messageQueue;
protected:
}



#endif /* DEVICE_H */

