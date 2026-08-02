#include "./FileServer.hpp"
#include "../HTTPResponse/HTTPResponse.hpp"
#include <winsock2.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdint>

// HTTP_Response_Class http_res;

void FILE_SERVER_Class::serveFile(SOCKET clientSocket, std::string &filePath, std::string &contentType){
     if (filePath.empty() || contentType.empty())
    {
        std::cout << "invalid filePath or conetentType\n";
        return;
    }

    if (clientSocket == INVALID_SOCKET)
    {
        std::cout << "invalid socket\n";
        return;
    }

    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        std::cout << filePath << "file cannot open!\n";
        std::string status = "404 Not found", contentType_ = "text/plain", contentLength = std::to_string(status.size()), body_ = status;
        std::string header = HTTP_Response_Class::setHeader(status, contentType_, contentLength, body_);
        send(clientSocket, header.c_str(), header.size(), 0);
        closesocket(clientSocket);
        return;
    }

    std::streamsize size = file.tellg();

    if (size == -1)
    {
        std::cout << "Failed to deremine file: " << filePath << "size\n";
        std::string status = "400 Bad request", contentType_ = "text/plain", contentLength = std::to_string(status.size()), body_ = status;
        std::string header = HTTP_Response_Class::setHeader(status, contentType_, contentLength, body_);
        send(clientSocket, header.c_str(), header.size(), 0);
        closesocket(clientSocket);
        return;
    }

    if (size == 0)
    {
        std::cout << "File is empty: " << filePath << "size\n";
        std::string status = "400 Bad request", contentType_ = "text/plain", contentLength = std::to_string(status.size()), body_ = status;
        std::string header = HTTP_Response_Class::setHeader(status, contentType_, contentLength, body_);
        send(clientSocket, header.c_str(), header.size(), 0);
        closesocket(clientSocket);
        return;
    }

    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> fileBuffer(static_cast<size_t>(size));
    if (!file.read(reinterpret_cast<char *>(fileBuffer.data()), size))
    {
        throw std::runtime_error("Failed reading file!\n");
    }

    std::string status = "200 OK", contentType_ = contentType, contentLength = std::to_string(size), body_ = "";
    std::string header = HTTP_Response_Class::setHeader(status, contentType_, contentLength, body_);

    send(clientSocket, header.c_str(), header.size(), 0);
    send(clientSocket, reinterpret_cast<char *>(fileBuffer.data()), static_cast<int>(fileBuffer.size()), 0);
    closesocket(clientSocket);
}