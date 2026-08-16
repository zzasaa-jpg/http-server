#ifndef HTTP_Response_HPP
#define HTTP_Response_HPP

#include <winsock2.h>
#include <string>
#include <iostream>

class HTTP_Response_Class
{

public:
    static std::string setHeader(
        const std::string &status, const std::string &contentType, const std::string &contentLength)
    {
        std::cout << " | " << status << std::endl;
        std::cout << "----------------------------\n";
        return "HTTP/1.1 " + status + "\r\n"
               "Content-Type: " + contentType + "\r\n"
               "Content-Length: " + contentLength + "\r\n" "\r\n";
    }
    static void sendData(SOCKET clientSocket, std::string &status, std::string &contentType, std::string &body)
    {
        std::string contentLength = std::to_string(body.size());
        std::string response = setHeader(status, contentType, contentLength) + body;
        send(clientSocket, response.c_str(), response.size(), 0);
        closesocket(clientSocket);
        return;
    }
};

#endif // HTTP_Response_HPP