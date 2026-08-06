#include "./HTTPRequest.hpp"

#include <iostream>

std::string nextToken(std::string &s, char delimiter)
{
    size_t pos = s.find(delimiter);
    if (pos == std::string::npos)
    {
        std::string token = s;
        s.clear();
        return token;
    }
    std::string token = s.substr(0, pos);
    s.erase(0, pos + 1);
    return token;
}

std::string nextLine(std::string &request)
{
    size_t pos = request.find("\r\n");
    if (pos == std::string::npos)
    {
        std::string token = request;
        request.clear();
        return token;
    }
    std::string line = request.substr(0, pos);
    request.erase(0, pos + 2);
    return line;
}

HTTP_Request HTTP_Request_Class::parse_http_request(std::string request)
{
    HTTP_Request http_req_struct;

    // Request line
    std::string requestLine = nextLine(request);
    http_req_struct.method = nextToken(requestLine, ' ');
    http_req_struct.path = nextToken(requestLine, ' ');
    http_req_struct.version = requestLine;

    // Headers
    while (!request.empty())
    {
        std::string line = nextLine(request);
        // End of header
        if (line.empty())
        {
            break;
        }
        size_t pos = line.find(':');
        if (pos == std::string::npos)
            continue;
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 2);

        http_req_struct.headers[key] = value;
    }

    // Body
    http_req_struct.body = request;
    return http_req_struct;
}