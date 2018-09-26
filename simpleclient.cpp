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
        int id = 1;
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


            ifstream file("/sys/class/gpio/gpio40/value");//чтение GPIO
            file.seekg (0, file.end);
            int length = file.tellg();
            file.seekg (0, file.beg);
            char * buffer = new char [length];
            file.read (buffer,1);
            file.close();
            
            json sDataValue;
            sDataValue ["DateTime"] = CustomDateTimeFormat(rawtime + i);
            sDataValue ["ID"] = id;
            sDataValue ["Status"] = 0;
            sDataValue ["Value"] = buffer;

            json OpenData;
            OpenData ["ConfigID"] = buffertime;
            //OpenData ["ConfigID"] = "11/1/17 11:59:52 AM";
            OpenData ["SN"] = SN;
            OpenData ["sDataValue"] = {sDataValue};
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

            json sVariable;
            sVariable ["Name"] = "GPIO40";
            sVariable ["ID"] = 1;
            sVariable ["AccessWrite"] = true;
            sVariable ["AccessRead"] = true;
            sVariable ["Archived"] = true;
            sVariable ["EngUnit"] = "";
            sVariable ["DataType"] = "INT32";

            json sRole;
            sRole ["ID"] = 1;
            sRole ["Role"] = "Value";

            json sFunctionalGroups;
            sFunctionalGroups["Name"] = "Value";
            sFunctionalGroups["sFunctionalGroups"] = nullptr;
            sFunctionalGroups["sRole"] = {sRole};

            json sFunctionalGroup;
            sFunctionalGroup["Name"] = "GPIO1";
            sFunctionalGroup["sFunctionalGroups"] = {sFunctionalGroups};
            sFunctionalGroup["sRole"] = nullptr;

            json sConfigDevice;
            sConfigDevice ["PropertyDescr"] = {PropertyDescr};
            sConfigDevice ["isPacked"] = "true";
            sConfigDevice ["sAlarm"] = {};
            sConfigDevice ["sVariable"] = {sVariable};
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