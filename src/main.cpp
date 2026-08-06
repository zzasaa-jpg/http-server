#include <iostream>
#include <winsock2.h>
#include "./WSAStartup/WSAStartup.hpp"
#include "./SOCKET/Socket.hpp"
#include "./HTTPResponse/HTTPResponse.hpp"
#include "./FileServer/FileServer.hpp"
#include "./MIME_type_detection/MIME_type_detection.hpp"
#include "./Logger/Logger.hpp"
#include "./HTTPRequest/HTTPRequest.hpp"

using namespace std;

FILE_SERVER_Class fileServe;
int main()
{
    Logger_Class log;
    HTTP_Request_Class parser;
    // WSA initialition
    wsastartup_Class wsa;
    int results = wsa.init();

    // Creating SOCKET
    SOCKET_Class sckt;

    if (sckt.Create_Socket() != 0)
    {
        return 1;
    }

    // Set the configureAddress of SOCKET
    if (sckt.configureAddress() != 0)
    {
        return 1;
    }

    // Bind the SOCKET
    if (sckt.bindSocket() != 0)
    {
        return 1;
    }

    // Listen the SOCKET
    if (sckt.listenSocket() != 0)
    {
        return 1;
    }

    log.init_log_file();

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

        std::string raw_request(buffer, received);
        HTTP_Request request = parser.parse_http_request(raw_request);
        if (request.method == "GET" && request.path == "/")
        {
            string body = "hello world!", contentType = MIME_TYPE_DETECTION_CLASS::get_MIME_Type("txt");
            HTTP_Response_Class::sendData(clientSocket, body, contentType);
        }
        else if (request.method == "GET" && request.path == "/favicon.ico")
        {
            string filePath = "../../src/Testing_files/favicon.ico", contentType = MIME_TYPE_DETECTION_CLASS::get_MIME_Type("ico");
            if (fileServe.serveFile(clientSocket, filePath, contentType) == false)
            {
                log.logger("Error", __FILE__, "file serve failed.");
            }
            else
            {
                log.logger("Success", __FILE__, "Successfully file served ico.");
            }
        }
        else if (request.method == "GET" && request.path == "/json")
        {
            string body = "{\"server\": \"Http\", \"lang\": \"C++\", \"array\": \"[1,2,3,4,5]\"}", contentType = MIME_TYPE_DETECTION_CLASS::get_MIME_Type("json");
            HTTP_Response_Class::sendData(clientSocket, body, contentType);
        }
        else if (request.method == "GET" && request.path == "/image")
        {
            string filePath = "../../src/Testing_files/image.jpg", contentType = MIME_TYPE_DETECTION_CLASS::get_MIME_Type("jpg");
            if (fileServe.serveFile(clientSocket, filePath, contentType) == false)
            {
                log.logger("Error", __FILE__, "file serve failed.");
            }
            else
            {
                log.logger("Success", __FILE__, "Successfully file served.");
            }
        }
        else if (request.method == "GET" && request.path == "/cpp")
        {
            string filePath = "../../src/main.cpp", contentType = MIME_TYPE_DETECTION_CLASS::get_MIME_Type("txt");
            if (fileServe.serveFile(clientSocket, filePath, contentType) == false)
            {
                log.logger("Error", __FILE__, "file serve failed.");
            }
            else
            {
                log.logger("Success", __FILE__, "Successfully file served.");
            }
        }
        else
        {
            string body = "404 Not Found", contentType = MIME_TYPE_DETECTION_CLASS::get_MIME_Type("txt");
            HTTP_Response_Class::sendData(clientSocket, body, contentType);
            log.logger("Message", __FILE__, body);
        }
    }
    sckt.close();
    WSACleanup();

    return 0;
}