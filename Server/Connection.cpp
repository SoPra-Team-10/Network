/**
 * @file Connection.cpp
 * @author paul
 * @date 10.03.19
 * @brief Implements the Connection class
 */

#include <utility>
#include "Connection.hpp"
#include "WebSocketServer.hpp"

namespace network {
    Connection::Connection(lws *socket, AsyncCallListPtr asyncCallList)
            : socket{socket}, callList{std::move(asyncCallList)}{}

    void Connection::send(std::string text) {
        if (!this->socket) {
            throw std::runtime_error("Client already disconnected");
        }
        std::lock_guard<std::mutex> lockGuard{callList->second};
        callList->first.emplace_back(std::bind(WebSocketServer::sendImpl, text, socket));
    }

    auto Connection::isValid() const -> bool {
        return !this->socket;
    }
}
