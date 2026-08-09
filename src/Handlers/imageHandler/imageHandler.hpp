#ifndef IMAGE_HANDLER_HPP
#define IMAGE_HANDLER_HPP

#include "../../HTTPRequest/HTTPRequest.hpp"
#include <winsock2.h>

void imageHandler(HTTP_Request request, SOCKET clientSocket);

#endif // IMAGE_HANDLER_HPP