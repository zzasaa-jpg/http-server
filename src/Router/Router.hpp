#ifndef ROUTER_HPP
#define ROUTER_HPP

#include "../HTTPRequest/HTTPRequest.hpp"
#include <winsock2.h>
#include <string>
#include <unordered_map>

class Router
{
public:
    void route(
        const std::string &Method, const std::string &Path,
        HTTP_Request request, SOCKET clientSocket);
    void registerRoute(
        const std::string &Method, const std::string &Path,
        void (*handler)(HTTP_Request request, SOCKET clientSocket));

private:
    std::unordered_map<std::string, void (*)(HTTP_Request request, SOCKET clientSocket)> Route_map;
};

#endif // ROUTER_HPP