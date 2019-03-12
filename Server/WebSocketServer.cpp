/**
 * @file WebSocketServer.cpp
 * @author paul
 * @date 10.03.19
 * @brief WebSocketServer @TODO
 */

#include "WebSocketServer.hpp"

namespace network {
    WebSocketServer::WebSocketServer(uint16_t port) :
        finished{false},
        callList{std::make_shared<std::list<std::function<void()>>>(),std::make_shared<std::mutex>()},
        context{nullptr, lws_context_destroy},
        protocols{
            {
                "http-only",
                &WebSocketServer::handler,
                sizeof(Connection),
                4096,
                0,
                nullptr,
                0
            },
            {
                nullptr, nullptr, 0, 0, 0, nullptr, 0 // Quasi null terminator
            }
        } {

        lws_context_creation_info contextCreationInfo{};
        contextCreationInfo.port = port;
        contextCreationInfo.protocols = this->protocols.data();
        contextCreationInfo.gid = -1;
        contextCreationInfo.uid = -1;

        this->context = decltype(this->context){lws_create_context(&contextCreationInfo),
                                                     lws_context_destroy};

        if (!this->context) {
            throw std::runtime_error("Could not initialize websocket");
        }

        this->workerThread = std::thread{&WebSocketServer::run, this};
    }

    void WebSocketServer::run() {
        while (!finished) {
            lws_service(this->context.get(), 50);

            this->callList.second->lock();
            for (const auto &call : *this->callList.first) {
                call();
            }
            this->callList.first->clear();
            this->callList.second->unlock();
        }
    }

    void WebSocketServer::sendImpl(std::string text, const std::unique_ptr<lws> &wsi) {
        lws_write(wsi.get(), reinterpret_cast<unsigned char*>(text.data()), text.length(), LWS_WRITE_TEXT);
    }

    WebSocketServer::~WebSocketServer() {
        finished = true;
        workerThread.join();
    }

    int WebSocketServer::handler(lws *websocket, lws_callback_reasons reasons, void *userData, void *data, size_t len) {
        auto *connection = static_cast<Connection*>(userData);
        std::string text{static_cast<char *>(data), len};

        switch (reasons) {
            case LWS_CALLBACK_PROTOCOL_INIT: {

                break;
            }
            case LWS_CALLBACK_PROTOCOL_DESTROY: {

                break;
            }
            case LWS_CALLBACK_ESTABLISHED: {

                break;
            }
            case LWS_CALLBACK_CLOSED: {

                break;
            }
            case LWS_CALLBACK_SERVER_WRITEABLE: {

                break;
            }
            case LWS_CALLBACK_RECEIVE: {
                break;
            }
            default:
                return 0;
        }

        return 0;
    }

}
