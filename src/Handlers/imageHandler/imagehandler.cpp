#include "./imageHandler.hpp"
#include "../../MIME_type_detection/MIME_type_detection.hpp"
#include "../../FileServer/FileServer.hpp"
#include "../../Logger/Logger.hpp"

void imageHandler(HTTP_Request request, SOCKET clientSocket)
{
    FILE_SERVER_Class fileServe;
    Logger_Class log;
    MIME_TYPE_DETECTION_CLASS mime_type;

    std::string filePath = "../../src/Testing_files/image.jpg", contentType = mime_type.get_MIME_Type("jpg");
    if (fileServe.serveFile(clientSocket, filePath, contentType) == false)
    {
        log.logger("Error", __FILE__, "file serve failed.");
    }
    else
    {
        log.logger("Success", __FILE__, "Successfully file served.");
    }
}