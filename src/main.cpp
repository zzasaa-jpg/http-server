#include <iostream>
#include <winsock2.h>
#include "./WSAStartup/WSAStartup.hpp"
#include "./SOCKET/Socket.hpp"
#include "./HTTPResponse/HTTPResponse.hpp"
#include "./FileServer/FileServer.hpp"
using namespace std;

FILE_SERVER_Class fileServe;
int main()
{
    // WSA initialition
    wsastartup_Class wsa;
    int results = wsa.init();

    // Creating SOCKET
    SOCKET_Class sckt;

    if(sckt.Create_Socket() != 0){
        return 1;
    }
    
    // Set the configureAddress of SOCKET
    if(sckt.configureAddress() != 0){
        return 1;
    }

    // Bind the SOCKET
    if(sckt.bindSocket() != 0){
        return 1;
    }

    // Listen the SOCKET
    if(sckt.listenSocket() != 0){
        return 1;
    }

    while (true)
    {
        // accept the Client SOCKET
        SOCKET clientSocket = sckt.acceptClient();
        char buffer[4096];

        int received = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (received <= 0)
        {
            std::cout << "recv failed: " << WSAGetLastError() << '\n';
            closesocket(clientSocket);
            continue;
        }

        std::string request(buffer, received);
        cout << request;
        if (request.find("GET /favicon.ico") != string::npos)
        {
            string filePath = "../../src/Testing_files/favicon.ico", contentType = "image/x-icon";
            fileServe.serveFile(clientSocket, filePath, contentType);
        }
        else if (request.find("GET /json") != string::npos)
        {
            string body = "{\"server\": \"Http\", \"lang\": \"C++\", \"array\": \"[1,2,3,4,5]\"}", contentType = "application/json";
            HTTP_Response_Class::sendData(clientSocket, body, contentType);
        }
        else if (request.find("GET /image") != string::npos)
        {
            string filePath = "../../src/Testing_files/image.jpg", contentType = "image/jpeg";
            fileServe.serveFile(clientSocket, filePath, contentType);
        }
        else if (request.find("GET /cpp") != string::npos)
        {
            string filePath = "../../src/main.cpp", contentType = "text/plain";
            fileServe.serveFile(clientSocket, filePath, contentType);
        }
        else
        {
            string body = "hello world!", contentType = "text/plain";
            HTTP_Response_Class::sendData(clientSocket, body, contentType);
        }
    }
    sckt.close();
    WSACleanup();

    return 0;
}