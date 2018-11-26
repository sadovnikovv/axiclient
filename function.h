/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   function.h
 * Author: v.sadovnikov
 *
 * Created on 26 ноября 2018 г., 9:35
 */

#ifndef FUNCTION_H
#define FUNCTION_H


int file_read(const char* filename, char* buffer, const unsigned buffer_size);
int gpio_read(int gpio, char* tt2);

typedef struct {
    int gpio_number;
    char* gpio_channel;
    char* gpio_value;
}GPIO;

#endif /* FUNCTION_H */

