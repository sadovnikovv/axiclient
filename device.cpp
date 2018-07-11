/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "device.h"

Device::Device(std::string serial){
this->serialNumber = new std::string(serial);
targetHost = nullptr;
targetPort =0;
socket = 0;
}

Device::~Device(){
    disconnect();
    delete serialNumber;

}

Device::connect(){
    // fix later
    // socket = socketopen(targetHost, targetPort);
}

Device::disconnect(){
    delete targetHost;
    targetPort =0;
    // fix later, implement socket close
    // socketclose(socket);
    socket = 0;
}

Device::send(json object){
    // конструируем и отсылаем
}

Device::recv(){
    // принимаем и возвращаем
}

Device::deviceSendAndRecv(){
    // полный цикл отправка и прием
}



