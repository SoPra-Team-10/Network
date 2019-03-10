/**
 * @file WebSocketServer.cpp
 * @author paul
 * @date 10.03.19
 * @brief WebSocketServer @TODO
 */

#include "WebSocketServer.hpp"

namespace network {
    lws_protocols WebSocketServer::protocols[] = {
        {
            "http-only",
            &WebSocketServer::callBackHttp,
            0,
        },
        {
            "otherProtocol",
            &WebSocketServer::callBackOther,
            0,
        },
        {
            nullptr, nullptr // Quasi null terminator
        }
    };

    WebSocketServer::WebSocketServer(uint16_t port) {
        lws_context_creation_info contextCreationInfo{};
        contextCreationInfo.port = port;
        contextCreationInfo.protocols = WebSocketServer::protocols;
        contextCreationInfo.gid = -1;
        contextCreationInfo.uid = -1;

        this->context = std::unique_ptr<lws_context>{lws_create_context(&contextCreationInfo)};

        if (!this->context) {
            throw std::runtime_error("Could not initialize websocket");
        }

        this->workerThread = std::thread{&WebSocketServer::run, this};
    }

    void WebSocketServer::run() {
        lws_service(this->context.get(), 50);

        this->toCallLock.lock();
        for (const auto &call : toCall) {
            call();
        }
        this->toCall.clear();
        this->toCallLock.unlock();
    }

    void WebSocketServer::send(const std::string &text) {
        toCallLock.lock();
        toCall.emplace_back(std::bind(&WebSocketServer::sendImpl, this, text));
        toCallLock.unlock();
    }

    void WebSocketServer::sendImpl(const std::string &text) {

    }

    int WebSocketServer::callBackHttp(lws *, lws_callback_reasons, void *, void *, std::size_t) {
        return 0;
    }

    int WebSocketServer::callBackOther(lws *, lws_callback_reasons, void *, void *, std::size_t) {
        return 0;
    }
}
