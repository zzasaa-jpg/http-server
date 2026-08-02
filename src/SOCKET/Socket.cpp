#include "./Socket.hpp"
#include <iostream>
#include <winsock2.h>

int SOCKET_Class::Create_Socket()
{
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (serverSocket == INVALID_SOCKET)
    {
        std::cout << "Socket connection failed!\n" << WSAGetLastError();
        WSACleanup();
        return 1;
    }

    return 0;
}

int SOCKET_Class::configureAddress()
{
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    return 0;
}

int SOCKET_Class::bindSocket()
{
    if (bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        std::cout << "Bind failed!\n" << WSAGetLastError() << std::endl;
        return 1;
    }
    return 0;
}

int SOCKET_Class::listenSocket()
{
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        std::cout << "Listen failed\n" << std::endl;
        return 1;
    }
    return 0;
}

SOCKET SOCKET_Class::acceptClient(){
    SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
    return clientSocket;
}

void SOCKET_Class::close(){
    closesocket(serverSocket);
}