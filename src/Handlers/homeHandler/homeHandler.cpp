#include "./homeHandler.hpp"
#include "../../HTTPResponse/HTTPResponse.hpp"
#include "../../MIME_type_detection/MIME_type_detection.hpp"

void homeHandler(HTTP_Request request, SOCKET clientSocket)
{
    MIME_TYPE_DETECTION_CLASS mime_type;
    std::string body = "hello world!", contentType = mime_type.get_MIME_Type("txt");
    HTTP_Response_Class::sendData(clientSocket, body, contentType);
}