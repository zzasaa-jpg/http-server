#include "./staticFIleServeHandler.hpp"
#include "../../MIME_type_detection/MIME_type_detection.hpp"
#include "../../Logger/Logger.hpp"
#include "../../FileServer/FileServer.hpp"

void staticFileServeHandler(HTTP_Request request, SOCKET clientSocket)
{
    Logger_Class log;
    MIME_TYPE_DETECTION_CLASS mime_type;
    FILE_SERVER_Class fileServe;

    std::string file_path = "../../src/main.cpp", contentType = mime_type.get_MIME_Type("txt");
    if (fileServe.serveFile(clientSocket, file_path, contentType) == false)
    {
        log.logger("Error", __FILE__, "file serve failed.");
    }
    else
    {
        log.logger("Success", __FILE__, "Successfully file served.");
    }
}