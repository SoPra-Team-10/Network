#include <gtest/gtest.h>

#include <SopraNetwork.h>

TEST(WebSocketServer, ConstructDeconstruct) {
    network::WebSocketServer server{8080};
    network::WebSocketServer{8081};
}
