#include "./FileServer.hpp"
#include "../HTTPResponse/HTTPResponse.hpp"
#include <winsock2.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdint>
#include "../Logger/Logger.hpp"
#include "../HTTPStatus_Code/HTTPStatus_Code.hpp"
#include "../MIME_type_detection/MIME_type_detection.hpp"

bool FILE_SERVER_Class::serveFile(SOCKET clientSocket, std::string &filePath, std::string &contentType)
{
    Logger_Class log;
    HTTPStatus_Code http_status_code;
    MIME_TYPE_DETECTION_CLASS mime_type;
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
        std::string status = http_status_code.Get_HTTPStatus_Code("404"), contentType_ = mime_type.get_MIME_Type("txt"), contentLength = std::to_string(status.size());
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
        std::string body = "File Content Length 0",
                    status = size != 0 ? http_status_code.Get_HTTPStatus_Code("200") : http_status_code.Get_HTTPStatus_Code("400"),
                    contentType_ = mime_type.get_MIME_Type("txt"),
                    contentLength = std::to_string(body.size());
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
    std::string status = http_status_code.Get_HTTPStatus_Code("200"), contentType_ = contentType, contentLength = std::to_string(size);
    std::string header = HTTP_Response_Class::setHeader(status, contentType_, contentLength);

    send(clientSocket, header.c_str(), header.size(), 0);
    send(clientSocket, reinterpret_cast<char *>(fileBuffer.data()), static_cast<int>(fileBuffer.size()), 0);
    closesocket(clientSocket);
    return true;
}