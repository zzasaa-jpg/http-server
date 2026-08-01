#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <vector>
#include <cstdint>
using namespace std;

string setHeader(string &status, string &contentType, string &contentLength, string &body)
{
    if (body.empty())
    {
        return "HTTP/1.1 " + status + "\r\n"
                                      "Content-Type: " +
               contentType + "\r\n"
                             "Content-Length: " +
               contentLength + "\r\n"
                               "\r\n";
    }
    else
    {
        return "HTTP/1.1 " + status + "\r\n"
                                      "Content-Type: " +
               contentType + "\r\n"
                             "Content-Length: " +
               contentLength + "\r\n"
                               "\r\n" +
               body;
    }
}

void serveFile(SOCKET clientSocket, string &filePath, string &contentType)
{
    if (filePath.empty() || contentType.empty())
    {
        cout << "invalid filePath or conetentType\n";
        return;
    }

    if (clientSocket == INVALID_SOCKET)
    {
        cout << "invalid socket\n";
        return;
    }

    ifstream file(filePath, ios::binary | ios::ate);
    if (!file.is_open())
    {
        cout << filePath << "file cannot open!\n";
        string status = "404 Not found", contentType_ = "text/plain", contentLength = to_string(status.size()), body_ = status;
        string header = setHeader(status, contentType_, contentLength, body_);
        send(clientSocket, header.c_str(), header.size(), 0);
        return;
    }

    streamsize size = file.tellg();

    if (size == -1)
    {
        cout << "Failed to deremine file" << filePath << "size\n";
        string status = "400 Bad request", contentType_ = "text/plain", contentLength = to_string(status.size()), body_ = status;
        string header = setHeader(status, contentType_, contentLength, body_);
        send(clientSocket, header.c_str(), header.size(), 0);
        return;
    }

    if (size == 0)
    {
        cout << "File is empty!" << filePath << "size\n";
        string status = "400 Bad request", contentType_ = "text/plain", contentLength = to_string(status.size()), body_ = status;
        string header = setHeader(status, contentType_, contentLength, body_);
        send(clientSocket, header.c_str(), header.size(), 0);
        return;
    }

    file.seekg(0, ios::beg);

    vector<uint8_t> fileBuffer(static_cast<size_t>(size));
    if (!file.read(reinterpret_cast<char *>(fileBuffer.data()), size))
    {
        throw runtime_error("Failed reading file!\n");
    }

    string status = "200 OK", contentType_ = contentType, contentLength = to_string(size), body_ = "";
    string header = setHeader(status, contentType_, contentLength, body_);

    send(clientSocket, header.c_str(), header.size(), 0);
    send(clientSocket, reinterpret_cast<char *>(fileBuffer.data()), static_cast<int>(fileBuffer.size()), 0);
    closesocket(clientSocket);
}

void sendData(SOCKET clientSocket, string &body, string &contentType)
{
    string status = "200 OK", contentType_ = contentType, contentLength = to_string(body.size()), body_ = body;
    string response = setHeader(status, contentType_, contentLength, body_);

    send(clientSocket, response.c_str(), response.size(), 0);
    closesocket(clientSocket);
}

int main()
{
    WSAData wsa;
    int results = WSAStartup(MAKEWORD(1, 1), &wsa);

    if (results != 0)
    {
        cout << "WSAStartup failed!\n"
             << results;
        WSACleanup();
        return 0;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (serverSocket == INVALID_SOCKET)
    {
        cout << "Socket connection failed!\n"
             << WSAGetLastError();
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr{};

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        cout << "Bind failed!\n"
             << WSAGetLastError();
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        cout << "Listen failed\n";
    }

    while (true)
    {

        SOCKET clientSocket = accept(
            serverSocket, nullptr, nullptr);

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
            string filePath = "../../src/favicon.ico", contentType = "image/x-icon";
            serveFile(clientSocket, filePath, contentType);
        }
        else if (request.find("GET /json") != string::npos)
        {
            string body = "{\"server\": \"Http\", \"lang\": \"C++\", \"array\": \"[1,2,3,4,5]\"}", contentType = "application/json";
            sendData(clientSocket, body, contentType);
        }
        else if (request.find("GET /image") != string::npos)
        {
            string filePath = "../../src/image.jpg", contentType = "image/jpeg";
            serveFile(clientSocket, filePath, contentType);
        }
        else if (request.find("GET /cpp") != string::npos)
        {
            string filePath = "../../src/txt.txt", contentType = "text/plain";
            serveFile(clientSocket, filePath, contentType);
        }
        else
        {
            string body = "hello world!", contentType = "text/plain";
            sendData(clientSocket, body, contentType);
        }
    }
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}