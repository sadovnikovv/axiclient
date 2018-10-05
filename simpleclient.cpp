/* 
 * File:   axiopcjsonclient.h
 * Author: v.sadovnikov
 *
 * Created on 26 октября 2017 г., 8:20
 */

#include <cstring>
#include <ctime>
#include <locale>
#include <string>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <stdio.h>

#include "axiopcjsonclient.h"
#include "json.hpp"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

        using json = nlohmann::json;
using namespace std;

string NETJavaScriptSerializerDateFormat(int64_t dateint) {
    stringstream ss;
    ss << dateint;
    string date(ss.str());
    string start = "\\/Date(";
    string end = ")\\/";
    date.insert(date.begin(), std::begin(start), std::end(start));
    date.append(end);
    return date;
}
//linked list

struct node {
    int data;
    node *next;
};

class linked_list {
private:
    node *head, *tail;
public:

    linked_list() {
        head = NULL;
        tail = NULL;
    }

    void add_node(int n) {
        node *tmp = new node;
        tmp->data = n;
        tmp->next = NULL;

        if (head == NULL) {
            head = tmp;
            tail = tmp;
        } else {
            tail->next = tmp;
            tail = tail->next;
        }
    }
};

/*Вермя для Time пример:\/Date(1509012173000+0300)\/  */

string CustomDateTimeFormat(int64_t dateint) {
    char temp_str[200]; // for time string
    memset(temp_str, 0, sizeof (temp_str));
    char temp_buffer[200]; // for formed datetime string
    memset(temp_buffer, 0, sizeof (temp_buffer));
    sprintf(temp_str, "%lu", (unsigned long) dateint);
    char byte_pre[] = {0x5C, 0x2F, 0x00};
    strcat(temp_buffer, byte_pre);
    strcat(temp_buffer, "Date("); // pre
    strcat(temp_buffer, temp_str); // body
    strcat(temp_buffer, "000+0300"); // do as milliseconds, and timezone
    strcat(temp_buffer, ")"); // post
    strcat(temp_buffer, byte_pre);
    stringstream ss;
    ss << temp_buffer;
    string date(ss.str());
    return date;
}

int main(int argc, char** argv) {
    /*Для определения начала вывода программы в консоли*/
    cout << "████─██─██─███─███─███─████─█──█" << endl;
    cout << "█──█──███───█───█──█───█──█─█──█" << endl;
    cout << "████───█────█───█──███─█────████" << endl;
    cout << "█──█──███───█───█──█───█──█─█──█" << endl;
    cout << "█──█─██─██─███──█──███─████─█──█" << endl;
    //Языки
    try {
        setlocale(LC_ALL, "rus");
        /*Время*/
        time_t rawtime;
        struct tm * timeinfo;
        char buffertime [80];
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffertime, 80, "%D %r", timeinfo);
        /*Статика*/
        int id = 1; //  убрать
        string SN = string(36, '3');
        int i;
        int sum = 0;
        char aa[] = "http://webtlm.ru:510";
        AxiOpcJsonClient *client = new AxiOpcJsonClient(aa);
        client->setTarget(aa);
        /*вывод в файл*/
        el::Loggers::addFlag(el::LoggingFlag::ColoredTerminalOutput);
        el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%datetime{%d/%M/%y %h:%m:%s,%g %F} %level -> %msg");
        cout << endl; //удалить позже
        LOG(INFO) << "Обычное сообщение";
        LOG(ERROR) << "Ошибка должна стать красной";
        LOG(WARNING) << "А предупреждение желтым";
        /* Цикл отправки сообщений */
        for (i = 1; i <= 400; i++) {
            cout << endl << endl << endl; //Интервал

            json sStatus;
            sStatus ["AlarmLevel"] = 0;
            sStatus ["Messages"] = {"Control chenal"};

            ifstream file24("/sys/class/gpio/gpio24/value");//чтение GPIO24
            file24.seekg (0, file24.end);
            int length24 = file24.tellg();
            file24.seekg (0, file24.beg);
            char * buffer24 = new char [length24];
            file24.read (buffer24,1);
            file24.close();
            
            ifstream file25("/sys/class/gpio/gpio25/value");//чтение GPIO25
            file25.seekg (0, file25.end);
            int length25 = file25.tellg();
            file25.seekg (0, file25.beg);
            char * buffer25 = new char [length25];
            file25.read (buffer25,1);
            file25.close();
            
            ifstream file26("/sys/class/gpio/gpio26/value");//чтение GPIO26
            file26.seekg (0, file26.end);
            int length26 = file26.tellg();
            file26.seekg (0, file26.beg);
            char * buffer26 = new char [length26];
            file26.read (buffer26,1);
            file26.close();
            
            ifstream file27("/sys/class/gpio/gpio27/value");//чтение GPIO27
            file27.seekg (0, file27.end);
            int length27 = file27.tellg();
            file27.seekg (0, file27.beg);
            char * buffer27 = new char [length27];
            file27.read (buffer27,1);
            file27.close();
            
            ifstream file28("/sys/class/gpio/gpio28/value");//чтение GPIO28
            file28.seekg (0, file28.end);
            int length28 = file28.tellg();
            file28.seekg (0, file28.beg);
            char * buffer28 = new char [length28];
            file28.read (buffer28,1);
            file28.close();
            
            ifstream file29("/sys/class/gpio/gpio29/value");//чтение GPIO29
            file29.seekg (0, file29.end);
            int length29 = file29.tellg();
            file29.seekg (0, file29.beg);
            char * buffer29 = new char [length29];
            file29.read (buffer29,1);
            file29.close();
            
            ifstream file30("/sys/class/gpio/gpio30/value");//чтение GPIO30
            file30.seekg (0, file30.end);
            int length30 = file30.tellg();
            file30.seekg (0, file30.beg);
            char * buffer30 = new char [length30];
            file30.read (buffer30,1);
            file30.close();
            
            ifstream file31("/sys/class/gpio/gpio31/value");//чтение GPIO31
            file31.seekg (0, file31.end);
            int length31 = file31.tellg();
            file31.seekg (0, file31.beg);
            char * buffer31 = new char [length31];
            file31.read (buffer31,1);
            file31.close();
            
            ifstream file32("/sys/class/gpio/gpio32/value");//чтение GPIO32
            file32.seekg (0, file32.end);
            int length32 = file32.tellg();
            file32.seekg (0, file32.beg);
            char * buffer32 = new char [length32];
            file32.read (buffer32,1);
            file32.close();
            
            ifstream file33("/sys/class/gpio/gpio33/value");//чтение GPIO33
            file33.seekg (0, file33.end);
            int length33 = file33.tellg();
            file33.seekg (0, file33.beg);
            char * buffer33 = new char [length33];
            file33.read (buffer33,1);
            file33.close();
            
            ifstream file34("/sys/class/gpio/gpio34/value");//чтение GPIO34
            file34.seekg (0, file34.end);
            int length34 = file34.tellg();
            file34.seekg (0, file34.beg);
            char * buffer34 = new char [length34];
            file34.read (buffer34,1);
            file34.close();
            
            ifstream file35("/sys/class/gpio/gpio35/value");//чтение GPIO35
            file35.seekg (0, file35.end);
            int length35 = file35.tellg();
            file35.seekg (0, file35.beg);
            char * buffer35 = new char [length35];
            file35.read (buffer35,1);
            file35.close();
            
            ifstream file40("/sys/class/gpio/gpio40/value");//чтение GPIO40
            file40.seekg (0, file40.end);
            int length40 = file40.tellg();
            file40.seekg (0, file40.beg);
            char * buffer40 = new char [length40];
            file40.read (buffer40,1);
            file40.close();
            
            ifstream file41("/sys/class/gpio/gpio41/value");//чтение GPIO41
            file41.seekg (0, file41.end);
            int length41 = file41.tellg();
            file41.seekg (0, file41.beg);
            char * buffer41 = new char [length41];
            file41.read (buffer41,1);
            file41.close();
            
            ifstream file42("/sys/class/gpio/gpio42/value");//чтение GPIO42
            file42.seekg (0, file42.end);
            int length42 = file42.tellg();
            file42.seekg (0, file42.beg);
            char * buffer42 = new char [length42];
            file42.read (buffer42,1);
            file42.close();
            
            ifstream file43("/sys/class/gpio/gpio43/value");//чтение GPIO43
            file43.seekg (0, file43.end);
            int length43 = file43.tellg();
            file43.seekg (0, file43.beg);
            char * buffer43 = new char [length43];
            file43.read (buffer43,1);
            file43.close();
            
            json sDataValue24;
            sDataValue24 ["DateTime"] = CustomDateTimeFormat(rawtime + i);
            sDataValue24 ["ID"] = 24;
            sDataValue24 ["Status"] = 0;
            sDataValue24 ["Value"] = 24;
//            sDataValue24 ["Value"] = buffer24;
            
            json sDataValue25;
            sDataValue25 ["DateTime"] = CustomDateTimeFormat(rawtime + i);
            sDataValue25 ["ID"] = 25;
            sDataValue25 ["Status"] = 0;
            sDataValue25 ["Value"] = 25;
//            sDataValue25 ["Value"] = buffer25;
            
            json sDataValue26;
            sDataValue26 ["DateTime"] = CustomDateTimeFormat(rawtime + i);
            sDataValue26 ["ID"] = 26;
            sDataValue26 ["Status"] = 0;
            sDataValue26 ["Value"] = 26;
//            sDataValue26 ["Value"] = buffer26;
            
            json sDataValue27;
            sDataValue27 ["DateTime"] = CustomDateTimeFormat(rawtime + i);
            sDataValue27 ["ID"] = 27;
            sDataValue27 ["Status"] = 0;
            sDataValue27 ["Value"] = buffer27;
            
            json sDataValue28;
            sDataValue28 ["DateTime"] = CustomDateTimeFormat(rawtime + i);
            sDataValue28 ["ID"] = 28;
            sDataValue28 ["Status"] = 0;
            sDataValue28 ["Value"] = buffer28;
            
            json sDataValue29;
            sDataValue29 ["DateTime"] = CustomDateTimeFormat(rawtime + i);
            sDataValue29 ["ID"] = 29;
            sDataValue29 ["Status"] = 0;
            sDataValue29 ["Value"] = buffer29;
            
            json sDataValue30;
            sDataValue30 ["DateTime"] = CustomDateTimeFormat(rawtime + i);
            sDataValue30 ["ID"] = 30;
            sDataValue30 ["Status"] = 0;
            sDataValue30 ["Value"] = buffer30;
            
            json sDataValue31;
            sDataValue31 ["DateTime"] = CustomDateTimeFormat(rawtime + i);
            sDataValue31 ["ID"] = 31;
            sDataValue31 ["Status"] = 0;
            sDataValue31 ["Value"] = buffer31;
            
            json sDataValue32;
            sDataValue32 ["DateTime"] = CustomDateTimeFormat(rawtime + i);
            sDataValue32 ["ID"] = 32;
            sDataValue32 ["Status"] = 0;
            sDataValue32 ["Value"] = buffer32;
            
            json sDataValue33;
            sDataValue33 ["DateTime"] = CustomDateTimeFormat(rawtime + i);
            sDataValue33 ["ID"] = 33;
            sDataValue33 ["Status"] = 0;
            sDataValue33 ["Value"] = buffer33;
            
            json sDataValue34;
            sDataValue34 ["DateTime"] = CustomDateTimeFormat(rawtime + i);
            sDataValue34 ["ID"] = 34;
            sDataValue34 ["Status"] = 0;
            sDataValue34 ["Value"] = buffer34;
            
            json sDataValue35;
            sDataValue35 ["DateTime"] = CustomDateTimeFormat(rawtime + i);
            sDataValue35 ["ID"] = 35;
            sDataValue35 ["Status"] = 0;
            sDataValue35 ["Value"] = buffer35;
            
            json sDataValue40;
            sDataValue40 ["DateTime"] = CustomDateTimeFormat(rawtime + i);
            sDataValue40 ["ID"] = 40;
            sDataValue40 ["Status"] = 0;
            sDataValue40 ["Value"] = buffer40;
            
            json sDataValue41;
            sDataValue41 ["DateTime"] = CustomDateTimeFormat(rawtime + i);
            sDataValue41 ["ID"] = 41;
            sDataValue41 ["Status"] = 0;
            sDataValue41 ["Value"] = buffer41;
            
            json sDataValue42;
            sDataValue42 ["DateTime"] = CustomDateTimeFormat(rawtime + i);
            sDataValue42 ["ID"] = 42;
            sDataValue42 ["Status"] = 0;
            sDataValue42 ["Value"] = buffer42;
            
            json sDataValue43;
            sDataValue43 ["DateTime"] = CustomDateTimeFormat(rawtime + i);
            sDataValue43 ["ID"] = 43;
            sDataValue43 ["Status"] = 0;
            sDataValue43 ["Value"] = buffer42;

            json OpenData;
            OpenData ["ConfigID"] = buffertime;
            //OpenData ["ConfigID"] = "11/1/17 11:59:52 AM";
            OpenData ["SN"] = SN;
            OpenData ["sDataValue"] = json::array({sDataValue27, sDataValue28, sDataValue29, sDataValue30, sDataValue31, sDataValue32, sDataValue33, sDataValue34, sDataValue35});
            OpenData ["sStatus"] = sStatus;

            json sOpenData;
            sOpenData ["id"] = id;
            sOpenData ["jsonrpc"] = "2.0";
            sOpenData ["method"] = "OpenData";
            sOpenData ["params"] = OpenData;

            json PropertyDescr;
            PropertyDescr ["id"] = 0;
            PropertyDescr ["Name"] = "Производитель";
            PropertyDescr ["Value"] = "Val-0";


            json sAlarm;
            sAlarm ["Name"] = "авария 1";
            sAlarm ["ID"] = 6;
            sAlarm ["AlarmMessage"] = "2:Дверь закрылась";
            sAlarm ["Priority"] = 0;

            
            json sVariable24;
            sVariable24 ["Name"] = "GPIO24";
            sVariable24 ["ID"] = 24;
            sVariable24 ["AccessWrite"] = true;
            sVariable24 ["AccessRead"] = true;
            sVariable24 ["Archived"] = true;
            sVariable24 ["EngUnit"] = "";
            sVariable24 ["DataType"] = "INT32";
            
            json sVariable25;
            sVariable25 ["Name"] = "GPIO25";
            sVariable25 ["ID"] = 25;
            sVariable25 ["AccessWrite"] = true;
            sVariable25 ["AccessRead"] = true;
            sVariable25 ["Archived"] = true;
            sVariable25 ["EngUnit"] = "";
            sVariable25 ["DataType"] = "INT32";
            
            json sVariable26;
            sVariable26 ["Name"] = "GPIO26";
            sVariable26 ["ID"] = 26;
            sVariable26 ["AccessWrite"] = true;
            sVariable26 ["AccessRead"] = true;
            sVariable26 ["Archived"] = true;
            sVariable26 ["EngUnit"] = "";
            sVariable26 ["DataType"] = "INT32";
            
            json sVariable27;
            sVariable27 ["Name"] = "GPIO27";
            sVariable27 ["ID"] = 27;
            sVariable27 ["AccessWrite"] = true;
            sVariable27 ["AccessRead"] = true;
            sVariable27 ["Archived"] = true;
            sVariable27 ["EngUnit"] = "";
            sVariable27 ["DataType"] = "INT32";
            
            json sVariable28;
            sVariable28 ["Name"] = "GPIO28";
            sVariable28 ["ID"] = 28;
            sVariable28 ["AccessWrite"] = true;
            sVariable28 ["AccessRead"] = true;
            sVariable28 ["Archived"] = true;
            sVariable28 ["EngUnit"] = "";
            sVariable28 ["DataType"] = "INT32";
            
            json sVariable29;
            sVariable29 ["Name"] = "GPIO29";
            sVariable29 ["ID"] = 29;
            sVariable29 ["AccessWrite"] = true;
            sVariable29 ["AccessRead"] = true;
            sVariable29 ["Archived"] = true;
            sVariable29 ["EngUnit"] = "";
            sVariable29 ["DataType"] = "INT32";
            
            json sVariable30;
            sVariable30 ["Name"] = "DIGI_IN1_INT ";
            sVariable30 ["ID"] = 30;
            sVariable30 ["AccessWrite"] = true;
            sVariable30 ["AccessRead"] = true;
            sVariable30 ["Archived"] = true;
            sVariable30 ["EngUnit"] = "";
            sVariable30 ["DataType"] = "INT32";
            
            json sVariable31;
            sVariable31 ["Name"] = "DIGI_IN2_INT ";
            sVariable31 ["ID"] = 31;
            sVariable31 ["AccessWrite"] = true;
            sVariable31 ["AccessRead"] = true;
            sVariable31 ["Archived"] = true;
            sVariable31 ["EngUnit"] = "";
            sVariable31 ["DataType"] = "INT32";
            
            json sVariable32;
            sVariable32 ["Name"] = "DIGI_IN3_INT ";
            sVariable32 ["ID"] = 32;
            sVariable32 ["AccessWrite"] = true;
            sVariable32 ["AccessRead"] = true;
            sVariable32 ["Archived"] = true;
            sVariable32 ["EngUnit"] = "";
            sVariable32 ["DataType"] = "INT32";
            
            json sVariable33;
            sVariable33 ["Name"] = "DIGI_IN4_INT ";
            sVariable33 ["ID"] = 33;
            sVariable33 ["AccessWrite"] = true;
            sVariable33 ["AccessRead"] = true;
            sVariable33 ["Archived"] = true;
            sVariable33 ["EngUnit"] = "";
            sVariable33 ["DataType"] = "INT32";
            
            json sVariable34;
            sVariable34 ["Name"] = "OUT_SW_EN0";
            sVariable34 ["ID"] = 34;
            sVariable34 ["AccessWrite"] = true;
            sVariable34 ["AccessRead"] = true;
            sVariable34 ["Archived"] = true;
            sVariable34 ["EngUnit"] = "";
            sVariable34 ["DataType"] = "INT32";
            
            json sVariable35;
            sVariable35 ["Name"] = "OUT_SW_EN1";
            sVariable35 ["ID"] = 35;
            sVariable35 ["AccessWrite"] = true;
            sVariable35 ["AccessRead"] = true;
            sVariable35 ["Archived"] = true;
            sVariable35 ["EngUnit"] = "";
            sVariable35 ["DataType"] = "INT32";
            
            json sVariable40;
            sVariable40 ["Name"] = "GPIO40";
            sVariable40 ["ID"] = 40;
            sVariable40 ["AccessWrite"] = true;
            sVariable40 ["AccessRead"] = true;
            sVariable40 ["Archived"] = true;
            sVariable40 ["EngUnit"] = "";
            sVariable40 ["DataType"] = "INT32";
            
            json sVariable41;
            sVariable41 ["Name"] = "GPIO41";
            sVariable41 ["ID"] = 41;
            sVariable41 ["AccessWrite"] = true;
            sVariable41 ["AccessRead"] = true;
            sVariable41 ["Archived"] = true;
            sVariable41 ["EngUnit"] = "";
            sVariable41 ["DataType"] = "INT32";
            
            json sVariable42;
            sVariable42 ["Name"] = "GPIO42";
            sVariable42 ["ID"] = 42;
            sVariable42 ["AccessWrite"] = true;
            sVariable42 ["AccessRead"] = true;
            sVariable42 ["Archived"] = true;
            sVariable42 ["EngUnit"] = "";
            sVariable42 ["DataType"] = "INT32";
            
            json sVariable43;
            sVariable43 ["Name"] = "GPIO43";
            sVariable43 ["ID"] = 43;
            sVariable43 ["AccessWrite"] = true;
            sVariable43 ["AccessRead"] = true;
            sVariable43 ["Archived"] = true;
            sVariable43 ["EngUnit"] = "";
            sVariable43 ["DataType"] = "INT32";
                
            json sRole24;
            sRole24 ["ID"] = 24;
            sRole24 ["Role"] = "Value";
            
            json sRole25;
            sRole25 ["ID"] = 25;
            sRole25 ["Role"] = "Value";
            
            json sRole26;
            sRole26 ["ID"] = 26;
            sRole26 ["Role"] = "Value";
            
            json sRole27;
            sRole27 ["ID"] = 27;
            sRole27 ["Role"] = "Value";
            
            json sRole28;
            sRole28 ["ID"] = 28;
            sRole28 ["Role"] = "Value";
            
            json sRole29;
            sRole29 ["ID"] = 29;
            sRole29 ["Role"] = "Value";
            
            json sRole30;
            sRole30 ["ID"] = 30;
            sRole30 ["Role"] = "Value";
            
            json sRole31;
            sRole31 ["ID"] = 31;
            sRole31 ["Role"] = "Value";
            
            json sRole32;
            sRole32 ["ID"] = 32;
            sRole32 ["Role"] = "Value";
            
            json sRole33;
            sRole33 ["ID"] = 33;
            sRole33 ["Role"] = "Value";
            
            json sRole34;
            sRole34 ["ID"] = 34;
            sRole34 ["Role"] = "Value";
            
            json sRole35;
            sRole35 ["ID"] = 35;
            sRole35 ["Role"] = "Value";
            
            json sRole40;
            sRole40 ["ID"] = 40;
            sRole40 ["Role"] = "Value";
            
            json sRole41;
            sRole41 ["ID"] = 41;
            sRole41 ["Role"] = "Value";
            
            json sRole42;
            sRole42 ["ID"] = 42;
            sRole42 ["Role"] = "Value";
            
            json sRole43;
            sRole43 ["ID"] = 43;
            sRole43 ["Role"] = "Value";
            
            json sFunctionalGroups1;
            sFunctionalGroups1["Name"] = "Давление";
            sFunctionalGroups1["sFunctionalGroups"] = nullptr;
            sFunctionalGroups1["sRole"] = json::array({sRole27, sRole28, sRole29, sRole30, sRole31, sRole32, sRole33, sRole34, sRole35});  
            
/*            json sFunctionalGroups;
            sFunctionalGroups["Name"] = "Давление1";
            sFunctionalGroups["sRole"] = nullptr;
            sFunctionalGroups["sFunctionalGroups"] = {sFunctionalGroups1};
*/

            json sFunctionalGroup;
            sFunctionalGroup["Name"] = "Тестовое устройство";
            sFunctionalGroup["sFunctionalGroups"] = {sFunctionalGroups1};
            sFunctionalGroup["sRole"] = nullptr;

            json sConfigDevice;
            sConfigDevice ["PropertyDescr"] = {PropertyDescr};
            sConfigDevice ["isPacked"] = "true";
            sConfigDevice ["sAlarm"] = {};
            sConfigDevice ["sVariable"] = json::array({sVariable27, sVariable28, sVariable29, sVariable30, sVariable31, sVariable32, sVariable33, sVariable34, sVariable35});
            sConfigDevice ["sFunctionalGroup"] = sFunctionalGroup;

            string message = sOpenData.dump(); //Запись для отправки на сервер
            string result; //Преременная на приём данных с сервера
            client->SendRPCMessage(message, result); //отправка на сервер
            if (result == "") {

                linked_list axi;
                continue;
            }
       
            LOG(INFO) << "Принято " << endl << result;
            json sOpenDataResponse;
            sOpenDataResponse = json::parse(result); //Парсим ответ sOpenDataResponse

            //cout << "JSON OBJECT: " << sOpenDataResponse.dump() << endl; // debug info
            json sOpenDataResponse_result = sOpenDataResponse["result"]; //Парсим result
            json sOpenDataResponse_session = sOpenDataResponse_result["SessionID"]; //Парсим SessionID в result
            json sOpenDataResponse_DataWriteValue = sOpenDataResponse_result["DataWriteValue"]; //Парсим DataWriteValue
            //json j_session = (j["result"])["SessionID"];
            string SessionID = sOpenDataResponse_result["SessionID"]; //создаём и записываем SessionID в переменную SessionID для SetMetaData
            bool updateFlag = sOpenDataResponse_result["isRequiredUpdate"]; //создаём и записываем isRequiredUpdate из sOpenDataResponse_result для дальнейшего цикла if (updateFlag)

            cout << "Парсим(" << i << "):  \n" << "DataWriteValue: " << sOpenDataResponse_DataWriteValue << ",   "
                    << "SessionID: " << SessionID << ",   " << "update: " << updateFlag << endl << endl;
            //updateFlag = true; // forcing update
            /*Проверяем T/F в isRequiredUpdate, если T, то кидаем SetMetaData*/
            if (sOpenDataResponse_DataWriteValue != nullptr)
            {
                cout << "sOpenDataResponse_DataWriteValue сработало" << endl;   
//                json j = json::parse(sOpenDataResponse_DataWriteValue);
                //говнозаглушка
                
                 /*string s; // сюда будем класть считанные строки
                 ifstream file("/sys/class/gpio/gpio34/value"); // файл из которого читаем ($
                 while(getline(file, s)){ // пока не достигнут конец файла класть очередную $
                 cout << s << endl; // выводим на экран
                 }
                 file.close();*/
                
                
                
                ifstream file228("/sys/class/gpio/gpio34/value");//чтение GPIO34
                file228.seekg (0, file228.end);
                int length228 = file228.tellg();
                file228.seekg (0, file228.beg);
                //char * buffer228 = new char [length228];
                char buffer228[1];
                file228.read (buffer228,1);
                file228.close();
                cout << buffer228 << endl;
//#define TEST 0
                // string s2 = "0";
                //if (strcmp(s.c_str(), s2.c_str()) == 0)
                if (buffer228[0] == 0x30)
                { ofstream fout;
                fout.open("/sys/class/gpio/gpio34/value");
                fout << "1";
                fout.close();
                }
                else
                {
                ofstream fout;
                fout.open("/sys/class/gpio/gpio34/value");
                fout << "0";
                fout.close();
                }
                //конец говнозаглушки
               
                //json DataWriteID = sOpenDataResponse_DataWriteValue["ID"];
               // json DataWriteValue = sOpenDataResponse_DataWriteValue["Value"];
                //cout << "ID: " << DataWriteID << "Value: " << DataWriteValue << endl;
            }
         
            if (updateFlag) {
            
                json SetMetaData;
                SetMetaData ["SessionID"] = SessionID;
                SetMetaData ["sConfigDevice"] = sConfigDevice;

                json rpcsetmetadata;
                rpcsetmetadata ["id"] = id;
                rpcsetmetadata ["jsonrpc"] = "2.0";
                rpcsetmetadata ["method"] = "SetMetaData";
                rpcsetmetadata ["params"] = SetMetaData;

                message = rpcsetmetadata.dump();
                client->SendRPCMessage(message, result);
                LOG(INFO) << "Принято " << endl << result;
                json sOpenDataResponse2;
                sOpenDataResponse2 = json::parse(result); //Парсим ответ sOpenDataResponse
                json sOpenDataResponse_result2 = sOpenDataResponse2["result"]; //Парсим result
                //        cout << sOpenDataResponse_result2 << endl;
                if (sOpenDataResponse_result2 == nullptr) {
                    cout << "Парсим SetMetaDataRespons:" << endl << "result: null" << endl; // можно работать с указателем
                } else {
                    LOG(WARNING) << "ERROR: reusult != null "; // here is error
                }
            }
            
            sum = sum + i;
        
    }
} catch (int asss) {
    cout << "arra" << asss << endl;
}
exit(0);
}