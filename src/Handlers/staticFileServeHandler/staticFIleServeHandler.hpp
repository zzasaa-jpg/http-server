#ifndef STATIC_FILE_SERVE_HPP
#define STATIC_FILE_SERVE_HPP

#include "../../HTTPRequest/HTTPRequest.hpp"
#include <winsock2.h>

void staticFileServeHandler(HTTP_Request request, SOCKET clientSocket);

#endif // STATIC_FILE_SERVE_HPP