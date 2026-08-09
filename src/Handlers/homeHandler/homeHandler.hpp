#ifndef HOME_HANDLER
#define HOME_HANDLER

#include "../../HTTPRequest/HTTPRequest.hpp"
#include <winsock2.h>

void homeHandler(HTTP_Request request, SOCKET clientSocket);

#endif // HOME_HANDLER