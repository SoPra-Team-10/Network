/**
 * @file ClientTest.cpp
 * @author paul
 * @date 13.03.19
 * @brief ClientTest @TODO
 */
#include <iostream>
#include <chrono>
#include <thread>

#include "../Client/WebSocketClient.hpp"

// Or use the installed version:
//#include <SopraNetwork/WebSocketClient.hpp>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"


int main() {
    using namespace std::chrono_literals;

    network::WebSocketClient client{"localhost", "/", 8080, "http-only"};

    auto handler = [](std::string s){
        std::cout << s << std::endl;
    };

    client.receiveListener(handler);

    while (true) {
        std::this_thread::sleep_for(1s);
        client.send("Test");
    }
    return 0;
}
#pragma clang diagnostic pop