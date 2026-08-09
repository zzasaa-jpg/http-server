#include <iostream>
#include <winsock2.h>
#include "./WSAStartup/WSAStartup.hpp"
#include "./SOCKET/Socket.hpp"
#include "./Logger/Logger.hpp"
#include "./HTTPRequest/HTTPRequest.hpp"
#include "./Router/Router.hpp"
#include "./Handlers/homeHandler/homeHandler.hpp"
#include "./Handlers/imageHandler/imageHandler.hpp"
#include "./Handlers/faviconHandler/faviconHandler.hpp"
#include "./Handlers/staticFileServeHandler/staticFIleServeHandler.hpp"

int main()
{
    Logger_Class log;
    HTTP_Request_Class parser;
    Router router;

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

    router.registerRoute("GET", "/", homeHandler);
    router.registerRoute("GET", "/image", imageHandler);
    router.registerRoute("GET", "/favicon.ico", faviconHandler);
    router.registerRoute("GET", "/cpp", staticFileServeHandler);

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
        std::cout << request.method << " | " << request.path << std::endl;

        router.route(request.method, request.path, request, clientSocket);
    }
    sckt.close();
    WSACleanup();

    return 0;
}