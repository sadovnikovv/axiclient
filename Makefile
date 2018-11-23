# * File:   Makefile
# Author: v.sadovnikov
# Created on 26 октября 2017 г., 8:20
# Тестовая сборка, в случае расширения программы поправить Makefile, как минимум добавить .cpp
#{Компилятор}{.cpp}{библиотеки}{-lz -o название файла}
#Test: 
#	g++ -std=c++11 simpleclient.cpp easylogging++.cc axiopcjsonclient.cpp -ljsoncpp -lcurl -ljsonrpccpp-common -ljsonrpccpp-client -lz -o Test
#apt-get install libz-dev
#apt-get install libcurl4-openssl-dev
#apt-get install libjsonrpccpp-dev libjsonrpccpp-tools
#apt-get install libjsoncpp-dev
#apt-get install libssl-dev
#apt-get install liblog4cpp5-dev
CC=g++
SOURCES=simpleclient.cpp easylogging++.cc axiopcjsonclient.cpp
LIB=-ljsoncpp -lcurl -ljsonrpccpp-common -ljsonrpccpp-client -lz 
STD="-std=c++11"
EXECUTABLE=Axitech_Test
$(EXECUTABLE):
	$(CC) $(STD) $(SOURCES) $(LIB) -o $@
clean:
	rm -rf *.o $(EXECUTABLE)