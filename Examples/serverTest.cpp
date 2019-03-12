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

void newConnectionHandler(std::shared_ptr<network::Connection> connection) {
    std::cout << "New Connection!" << std::endl;
    connection->send("Pong");
}

int main() {
    network::WebSocketServer server{8080};
    decltype(network::WebSocketServer::connectionListener)::type handler{newConnectionHandler};
    network::WebSocketServer::connectionListener(handler);
    std::cout << "Started on port 8080" << std::endl;
    while (true) {

    }
}
 