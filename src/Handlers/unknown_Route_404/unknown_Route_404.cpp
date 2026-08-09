#include "./unknown_Route_404.hpp"
#include "../../HTTPResponse/HTTPResponse.hpp"
#include "../../MIME_type_detection/MIME_type_detection.hpp"
#include "../../Logger/Logger.hpp"

void unknown_Route(HTTP_Request request, SOCKET clientSocket)
{
    Logger_Class log;
    MIME_TYPE_DETECTION_CLASS mime_type;

    std::string body = "404 Not Found", contentType = mime_type.get_MIME_Type("txt");
    HTTP_Response_Class::sendData(clientSocket, body, contentType);
    log.logger("Message", __FILE__, body);
}