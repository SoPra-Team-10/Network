#include <utility>

/**
 * @file ConnectionInformation.cpp
 * @author paul
 * @date 10.03.19
 * @brief ConnectionInformation @TODO
 */

#include "Connection.hpp"
#include "WebSocketServer.hpp"

namespace network {
    Connection::Connection(lws *socket, AsyncCallList asyncCallList)
            : socket{socket}, callList{std::move(asyncCallList)}{}

    void Connection::send(std::string text) {
        std::lock_guard<std::mutex> lockGuard{callList->second};
        callList->first.emplace_back([=](){WebSocketServer::sendImpl(text, this->socket);});
    }
}
