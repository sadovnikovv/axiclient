/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "function.h"

// return 0 on success, return -1 on error
int file_read(const char* filename, char* buffer, const unsigned buffer_size) {
    int status;
    buffer[0]=0;
    buffer[1]=0;

    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        // error
        
        std::cout << "Не смог открыть файл! Выход. " << std::endl;
        
        return -1;
    }

    status = fseek(file, 0, SEEK_SET);
    if (status != 0) {
        // error
        return -1;
    }
    //read
    status = fread(&buffer[0], 1, 1, file);
    if (status != 1) {
        // error
        return -1;
    }

    status = fclose(file);
    if (status != 0) {
        // error
        return -1;
    }

    return 0;
}

int gpio_read(int gpio, char* tt2){
            std::string str;
            std::string str_prefix="/sys/class/gpio/gpio";
            std::string str_suffix="/value";

            str.append(str_prefix);
            
            char *temp = new char[16];
            sprintf(temp, "%d", gpio);
            //str.append(itoa(gpio));
            str.append(temp);
            str.append(str_suffix);
            
            //file_read("/sys/class/gpio/gpio28/value", temp_buffer, sizeof(temp_buffer));
            return file_read(str.c_str(), &tt2[0], 2);
            //memcpy (&tt2[gpio][0], &temp_buffer[0], 2);

}