#include "./faviconHandler.hpp"
#include "../../MIME_type_detection/MIME_type_detection.hpp"
#include "../../FileServer/FileServer.hpp"
#include "../../Logger/Logger.hpp"

void faviconHandler(HTTP_Request request, SOCKET clientSocket)
{
    Logger_Class log;
    FILE_SERVER_Class fileServe;
    MIME_TYPE_DETECTION_CLASS mime_type;

    std::string filePath = "../../src/Testing_files/favicon.ico", contentType = mime_type.get_MIME_Type("ico");
    if (fileServe.serveFile(clientSocket, filePath, contentType) == false)
    {
        log.logger("Error", __FILE__, "file serve failed ico.");
    }
    else
    {
        log.logger("Success", __FILE__, "Successfully file served ico.");
    }
}