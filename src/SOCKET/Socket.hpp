#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <winsock2.h>

class SOCKET_Class{
    public:
        int Create_Socket();
        int configureAddress();
        int bindSocket();
        int listenSocket();
        SOCKET acceptClient();
        void close();
    private:
        SOCKET serverSocket;
        sockaddr_in serverAddr;
};

#endif // SOCKET