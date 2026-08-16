#include "./unknown_Route_404.hpp"
#include "../../HTTPResponse/HTTPResponse.hpp"
#include "../../MIME_type_detection/MIME_type_detection.hpp"
#include "../../Logger/Logger.hpp"
#include "../../HTTPStatus_Code/HTTPStatus_Code.hpp"

void unknown_Route(HTTP_Request request, SOCKET clientSocket)
{
    Logger_Class log;
    MIME_TYPE_DETECTION_CLASS mime_type;
    HTTPStatus_Code http_status_code;

    std::string status = http_status_code.Get_HTTPStatus_Code("404"),
                contentType = mime_type.get_MIME_Type("txt"), body = "404 Not Found";
    HTTP_Response_Class::sendData(clientSocket, status, contentType, body);
    log.logger("Message", __FILE__, status);
}