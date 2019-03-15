#include <gtest/gtest.h>

#ifdef USE_INSTALLED_LIB
#include <SopraNetwork/WebSocketServer.hpp>
#else
#include <Server/WebSocketServer.hpp>
#endif

TEST(WebSocketServer, ConstructDeconstruct) {
    EXPECT_NO_THROW((network::WebSocketServer{8080, "abc"}));
    EXPECT_NO_THROW((network::WebSocketServer{8081, "http-only"}));
}
