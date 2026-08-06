#ifndef HTTP_Request_HPP
#define HTTP_Request_HPP

#include <string>
#include <map>

struct HTTP_Request
{
    std::string method;
    std::string path;
    std::string version;
    std::map<std::string, std::string> headers;
    std::string body;
};

class HTTP_Request_Class
{
public:
    HTTP_Request parse_http_request(std::string request);
};

#endif // HTTP_Request_HPP