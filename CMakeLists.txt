cmake_minimum_required(VERSION 3.10)

project(HTTP_Server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/executable_code)

add_executable(server
    src/main.cpp
    src/WSAStartup/WSAStartup.cpp
    src/SOCKET/Socket.cpp
    src/FileServer/FileServer.cpp
    src/Logger/Logger.cpp
    src/HTTPRequest/HTTPRequest.cpp
)

target_link_libraries(server PRIVATE ws2_32)