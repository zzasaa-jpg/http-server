#ifndef HTTP_Response_HPP
#define HTTP_Response_HPP

#include <winsock2.h>
#include <string>

class HTTP_Response_Class{
    public:
        static std::string setHeader(
            const std::string &status, const std::string &contentType,
            const std::string &contentLength, const std::string &body){
                if (body.empty())
                {
                    return "HTTP/1.1 " + status + "\r\n"
                        "Content-Type: " + contentType + "\r\n"
                        "Content-Length: " +contentLength + "\r\n" "\r\n";
                }
                else
                {
                    return "HTTP/1.1 " + status + "\r\n"
                        "Content-Type: " + contentType + "\r\n"
                        "Content-Length: " + contentLength + "\r\n" "\r\n" + body;
                }
            }
        static void sendData(SOCKET clientSocket, std::string &body, std::string &contentType){
            std::string status = "200 OK", contentType_ = contentType, contentLength = std::to_string(body.size()), body_ = body;
            std::string response = setHeader(status, contentType_, contentLength, body_);
            send(clientSocket, response.c_str(), response.size(), 0);
            closesocket(clientSocket);
            return;
        }
};

#endif // HTTP_Response_HPP