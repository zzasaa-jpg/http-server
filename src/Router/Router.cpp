#include "./Router.hpp"
#include "../Handlers/unknown_Route_404/unknown_Route_404.hpp"

#include <iostream>

void Router::registerRoute(
    const std::string &Method, const std::string &Path,
    void (*handler)(HTTP_Request request, SOCKET clientSocket))
{
    std::string key = Method + " " + Path;
    Route_map[key] = handler;
}

void Router::route(
    const std::string &Method, const std::string &Path,
    HTTP_Request request, SOCKET clientSocket)
{
    std::string key = Method + " " + Path;
    auto route = Route_map.find(key);
    if (route == Route_map.end())
    {
        std::cout << "not found\n";
        unknown_Route(request, clientSocket);
        return;
    }
    route->second(request, clientSocket);
}