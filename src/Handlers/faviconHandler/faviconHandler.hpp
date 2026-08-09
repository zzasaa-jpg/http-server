#ifndef FAVICON_HANDLER_HPP
#define FAVICON_HANDLER_HPP

#include "../../HTTPRequest/HTTPRequest.hpp"
#include <winsock2.h>

void faviconHandler(HTTP_Request request, SOCKET clientSocket);

#endif // FAVICON_HANDLER_HPP