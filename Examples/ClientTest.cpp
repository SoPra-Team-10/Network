/**
 * @file ClientTest.cpp
 * @author paul
 * @date 13.03.19
 * @brief ClientTest @TODO
 */
#include <iostream>

#include "../Client/WebSocketClient.hpp"

// Or use the installed version:
//#include <SopraNetwork/WebSocketClient.hpp>

int main() {
    network::WebSocketClient client{"localhost", "/", 8080, "http-only"};

    while (true) {

    }
    return 0;
}