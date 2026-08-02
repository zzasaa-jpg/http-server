#include "../../src/WSAStartup/WSAStartup.hpp"
#include <iostream>
#include <winsock2.h>

int wsastartup_Class::init(){
    WSAData wsa;
    int results = WSAStartup(MAKEWORD(1, 1), &wsa);

    if (results != 0)
    {
        std::cout << "WSAStartup failed: " << results << std::endl;
        WSACleanup();
        return results;
    }
    return results;
}