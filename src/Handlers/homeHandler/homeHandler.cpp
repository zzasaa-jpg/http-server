#include "./homeHandler.hpp"
#include "../../HTTPResponse/HTTPResponse.hpp"
#include "../../MIME_type_detection/MIME_type_detection.hpp"
#include "../../HTTPStatus_Code/HTTPStatus_Code.hpp"

void homeHandler(HTTP_Request request, SOCKET clientSocket)
{
    MIME_TYPE_DETECTION_CLASS mime_type;
    HTTPStatus_Code http_status_code;

    std::string status = http_status_code.Get_HTTPStatus_Code("200"),
                body = "hello world!", contentType = mime_type.get_MIME_Type("txt");
    HTTP_Response_Class::sendData(clientSocket, status, contentType, body);
}