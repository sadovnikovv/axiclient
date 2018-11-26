/* 
 * File:   axiopcjsonclient.cpp
 * Author: v.sadovnikov
 *
 * Created on 26 октября 2017 г., 8:20
 */

#include "axiopcjsonclient.h"
#include "easylogging++.h"


#include <iostream>
#include <curl/curl.h>
#include <string>
#include <cstdlib>
#include <cstring>
#include <zlib.h>
#include <inttypes.h>


using namespace std;
using nlohmann::json;

char *_replace_string(char *str, const char *what, const char *with) {
    char *ptr; // work pointer

    char *tail_str = NULL;
    size_t tail_length = 0;
    if (str == NULL || what == NULL || with == NULL) {
        printf("_replace_string NULL arguments: %s %s %s\n", str, what, with);
        return NULL;
    }
    if (strcmp(str, "") == 0) {
        //printf("Empty string, nothing to process\n");
        LOG(ERROR) << "Пустая срока, ничего не обработать." << endl;


        //return NULL;
        //throw 555;
    }
    if (strcmp(what, "") == 0) {
        printf("Empty string what to replace\n");
        return NULL;
    }
    ptr = strstr(str, what); // lookup
    while (ptr != NULL) {
        tail_length = strlen(ptr + strlen(what)); // tail length after 'what' substring
        tail_str = new char[tail_length + 1];
        memset(&tail_str[0], 0, (tail_length + 1));
        strcpy(&tail_str[0], ptr + strlen(what)); // copy tail after 'what' substring
        strcpy(ptr, with); // copy replace
        strcat(str, tail_str); // add tail
        delete[] tail_str; // no longer need, free
        ptr = strstr(str, what); // lookup next
    }
    return str; // we are done
}

class curl_initializer {
public:

    curl_initializer() {
        curl_global_init(CURL_GLOBAL_ALL);
    }

    ~curl_initializer() {
        curl_global_cleanup();
    }
};

static curl_initializer _curl_init = curl_initializer();

struct string11 {
    char *ptr;
    size_t len;
};

std::string decompress_string(const std::string &str) {
    z_stream zs;
    memset(&zs, 0, sizeof (zs));

    if (inflateInit(&zs) != Z_OK)
        std::cout << "inflateInit failed while decompressing.";

    zs.next_in = (Bytef *) str.data();
    zs.avail_in = str.size();

    int ret;
    char outbuffer[32768];
    std::string outstring;

    do {
        zs.next_out = reinterpret_cast<Bytef *> (outbuffer);
        zs.avail_out = sizeof (outbuffer);

        ret = inflate(&zs, 0);

        if (outstring.size() < zs.total_out) {
            outstring.append(outbuffer,
                    zs.total_out - outstring.size());
        }

    } while (ret == Z_OK);

    inflateEnd(&zs);

    if (ret != Z_STREAM_END) {
        std::ostringstream oss;
        oss << "Exception during zlib decompression: (" << ret << ") "
                << zs.msg;
    }

    return outstring;
}

static int wait_on_socket(curl_socket_t sockfd, int for_recv, long timeout_ms) {
    struct timeval tv;
    fd_set infd, outfd, errfd;
    int res;
    cout << "Поиск утечки времени 1" << endl;
    tv.tv_sec = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;

    FD_ZERO(&infd);
    FD_ZERO(&outfd);
    FD_ZERO(&errfd);

    FD_SET(sockfd, &errfd);

    if (for_recv) {
        FD_SET(sockfd, &infd);
    } else {
        FD_SET(sockfd, &outfd);
    }

    res = select(sockfd + 1, &infd, &outfd, &errfd, &tv);
    return res;
}

void init_string(struct string11 *s) {
    s->len = 0;
    s->ptr = (char *) malloc(s->len + 1);
    s->ptr[0] = '\0';
}

AxiOpcJsonClient::AxiOpcJsonClient(const std::string &url)
: url(url) {
    this->timeout = 5000; //здесь бывает баг arr666
    curl = curl_easy_init();
        cout << "Поиск утечки времени 2" << endl;
}

AxiOpcJsonClient::~AxiOpcJsonClient() {
    curl_easy_cleanup(curl);
}

void AxiOpcJsonClient::SendRPCMessage(const std::string &message, std::string &result) {

    cout << "message: " << message << endl;


    // changed message
    //    char temp_test[2048];//в этот размер влезает 9 gpio каналов
    char temp_test[65535]; //размер буфера на отправку (больше сообщений -> больше буфер)
    memset(temp_test, 0, sizeof (temp_test));
    strcpy(temp_test, message.c_str());
    char what[] = {0x5C, 0x5C, 0};
    char with[] = {0x5C, 0};
    char with_PH[] = {static_cast<char> (0xff), static_cast<char> (0xff), 0};
    try {
        _replace_string(temp_test, what, with_PH);
        _replace_string(temp_test, with_PH, with);
    } catch (int ex) {
        cout << "Got exception: " << ex << endl;
        cout << "Throw 560" << endl;
        throw 560;
    }

    int32_t axiheader = (int32_t) strlen(temp_test);

    char *request = new char[4];
    memset(request, 0, 4);
    std::strcpy(request, (char *) &axiheader);

    CURLcode res;
    curl_socket_t sockfd;
    long sockextr;
    size_t iolen;
    curl_off_t nread;

    curl_easy_setopt(curl, CURLOPT_URL, this->url.c_str());
    curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, timeout);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::stringstream str;
        str << "libcurl error: " << res;
        if (res == 7)
            str << " -> Could not connect to " << "webtlm.ru:510";
        else if (res == 28)
            str << " -> Operation timed out";
        throw 666;
    }
    res = curl_easy_getinfo(curl, CURLINFO_LASTSOCKET, &sockextr);
    if (CURLE_OK != res) {
        printf("Error: %s\n", curl_easy_strerror(res));
        return;
    }
    sockfd = (curl_socket_t) sockextr;
    if (!wait_on_socket(sockfd, 0, 10000L)) {
        std::cout << ("Timeout error.") << std::endl;
        return;
    }
    int32_t i;
    res = curl_easy_send(curl, request, 4, &iolen);
    nread = (curl_off_t) iolen;
    memcpy(&i, request, sizeof (int32_t));
    res = curl_easy_send(curl, temp_test, strlen(temp_test), &iolen);
    nread = (curl_off_t) iolen;
    LOG(INFO) << "Отправлено " << endl << temp_test;
    cout << endl;
    if (CURLE_OK != res) {
        //printf("Error: %s\n", curl_easy_strerror(res));
        LOG(ERROR) << "Error: " << curl_easy_strerror(res) << endl;
        ;
        return;
    }
    //std::cout << "Reading header ";
    bool compressed = false;
    for (;;) {
        char buf[4096];
        memset(buf, 0, sizeof (buf));
        if (!wait_on_socket(sockfd, 1, 10000L)) {
            std::cout << ("Timeout error.") << std::endl;
            return;
        }
        res = curl_easy_recv(curl, buf, sizeof (buf), &iolen);
        if (iolen == 4) {
            memcpy(&i, buf, sizeof (int32_t));
            if ((i >> 31) & 1)
                compressed = true;
        }
        if (CURLE_OK != res)
            break;
        nread = (curl_off_t) iolen;
        //printf("response %"
        //       CURL_FORMAT_CURL_OFF_T
        //    " bytes:\n", nread);
        if (iolen != 4 && compressed) {
            char temp2[4097];
            memset(temp2, 0, sizeof (temp2));
            //result = decompress_string(std::string(buf));
            strcpy(temp2, decompress_string(std::string(buf)).c_str());
            // std::cout << "OLD PLAIN: " << std::string(temp2) << std::endl;
            char what_4[] = "\"id\":\"1\"";
            char with_4[] = "\"id\":1";
            try {
                _replace_string(temp2, what_4, with_4);
            } catch (int ex) {
                cout << "Got exception: " << ex << endl;
                cout << "Throw 561" << endl;
                throw 561;
            }

            // -- some replace magic
            //
            result = std::string(temp2);
            std::cout << "result: " << std::string(temp2) << std::endl;
            //std::cout << "DECOMPRESS: " << result << std::endl;
            break;
        } else if (iolen != 4) {
            char what_4[] = "\"id\":\"1\"";
            char with_4[] = "\"id\":1";
            try {
                _replace_string(buf, what_4, with_4);
            } catch (int e) {
                cout << "Got exception: " << e << endl;
                cout << "Разрыв соединения" << endl;
                LOG(ERROR) << "Разрыв соединения";
                throw 562;
            }

            // -- some replace magic
            result = std::string(buf);
            //std::cout << "Принято: \n" << std::string(buf) << std::endl;
            break;
        } else {
            //std::cout << "SOME: " << i << std::endl;
        }
    }
    //
    // printf("RPC cycle done.\n");



}

void AxiOpcJsonClient::SetUrl(const std::string &url) {
    this->url = url;
}

void AxiOpcJsonClient::SetTimeout(long timeout) {
    this->timeout = timeout;
}

void AxiOpcJsonClient::AddHeader(const std::string &attr, const std::string &val) {
    this->headers[attr] = val;
}

void AxiOpcJsonClient::RemoveHeader(const std::string &attr) {
    this->headers.erase(attr);
}
