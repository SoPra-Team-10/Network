#include <gtest/gtest.h>

#ifdef USE_INSTALLED_LIB
#include <SopraNetwork/WebSocketServer.hpp>
#else
#include <Server/WebSocketServer.hpp>
#endif

TEST(WebSocketServer, ConstructDeconstruct) {
    network::WebSocketServer server{8080};
    network::WebSocketServer{8081};
}
