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

int main() {
    network::WebSocketServer server{8080};
    std::cout << "Started on port 8080" << std::endl;
    while (true) {

    }
}
 