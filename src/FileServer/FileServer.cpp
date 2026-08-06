#include "./FileServer.hpp"
#include "../HTTPResponse/HTTPResponse.hpp"
#include <winsock2.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdint>
#include "../Logger/Logger.hpp"

bool FILE_SERVER_Class::serveFile(SOCKET clientSocket, std::string &filePath, std::string &contentType)
{
    Logger_Class log;
    if (filePath.empty() || contentType.empty())
    {
        std::cout << "invalid filePath or conetentType\n";
        log.logger("Error", __FILE__, "invalid filePath or conetentType.");
        return false;
    }

    if (clientSocket == INVALID_SOCKET)
    {
        std::cout << "invalid socket\n";
        log.logger("Error", __FILE__, "invalid socket.");
        return false;
    }

    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        std::cout << filePath << ": file cannot open!\n";
        log.logger("Error", __FILE__, "file cannot open.");
        std::string status = "404 Not found", contentType_ = "text/plain", contentLength = std::to_string(status.size());
        std::string header = HTTP_Response_Class::setHeader(status, contentType_, contentLength) + status;
        send(clientSocket, header.c_str(), header.size(), 0);
        closesocket(clientSocket);
        return false;
    }

    std::streamsize size = file.tellg();

    if (size == -1 || size == 0)
    {
        if (size == 0)
            std::cout << "-- FILE IS EMPTY => " << filePath << "\n";
        else
            std::cout << "-- Failed to deremine file size.\n";
        std::string body = "File Content Length 0", status = size == 0 ? "200 OK" : "400 Bad request", contentType_ = "text/plain", contentLength = std::to_string(body.size());
        std::string header = HTTP_Response_Class::setHeader(status, contentType_, contentLength) + (size == 0 ? body : "|");
        send(clientSocket, header.c_str(), header.size(), 0);
        closesocket(clientSocket);
        return false;
    }

    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> fileBuffer(static_cast<size_t>(size));
    if (!file.read(reinterpret_cast<char *>(fileBuffer.data()), size))
    {
        throw std::runtime_error("Failed reading file!\n");
    }

    std::string status = "200 OK", contentType_ = contentType, contentLength = std::to_string(size);
    std::string header = HTTP_Response_Class::setHeader(status, contentType_, contentLength);

    send(clientSocket, header.c_str(), header.size(), 0);
    send(clientSocket, reinterpret_cast<char *>(fileBuffer.data()), static_cast<int>(fileBuffer.size()), 0);
    closesocket(clientSocket);
    return true;
}