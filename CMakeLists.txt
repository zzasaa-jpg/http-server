cmake_minimum_required(VERSION 3.10)

project(HTTP_Server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/executable_code)

add_executable(server
    src/main.cpp
    src/WSAStartup/WSAStartup.cpp
    src/SOCKET/Socket.cpp
    src/MIME_type_detection/MIME_type_detection.cpp
    src/FileServer/FileServer.cpp
    src/Logger/Logger.cpp
    src/HTTPRequest/HTTPRequest.cpp
    src/Router/Router.cpp
    src/Handlers/homeHandler/homeHandler.cpp
    src/Handlers/faviconHandler/faviconHandler.cpp
    src/Handlers/imageHandler/imageHandler.cpp
    src/Handlers/unknown_Route_404/unknown_Route_404.cpp
    src/Utilities/File_Name/File_Name.cpp
    src/Handlers/staticFileServeHandler/staticFileServeHandler.cpp
)

target_link_libraries(server PRIVATE ws2_32)