#ifndef FILE_SERVER_HPP
#define FILE_SERVER_HPP

#include <winsock2.h>
#include <string>

class FILE_SERVER_Class{
    public:
        bool serveFile(SOCKET clientSocket, std::string &filePath, std::string &contentType);
};

#endif // FILE_SERVER_HPP