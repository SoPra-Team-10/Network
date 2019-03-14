/**
 * @file serverTest.cpp
 * @author paul
 * @date 11.03.19
 * @brief Small websockets server
 */
#include <iostream>

#include "../Server/WebSocketServer.hpp"

// Or use the installed version:
//#include <SopraNetwork/WebSocketServer.hpp>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void newConnectionHandler(std::shared_ptr<network::Connection> connection) {
    std::cout << "New Connection!" << std::endl;
    connection->send("Pong");
    std::function<void(std::string)> receiveHandler = [](std::string text){
        std::cout << "Received: " << text << std::endl;
    };
    connection->receiveListener(receiveHandler);
}

int main() {
    network::WebSocketServer server{8080, "http-only"};
    decltype(server.connectionListener)::type handler{newConnectionHandler};
    server.connectionListener(handler);
    std::cout << "Started on port 8080" << std::endl;
    while (true) {

    }
}

#pragma clang diagnostic pop