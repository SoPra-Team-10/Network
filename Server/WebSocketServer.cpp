/**
 * @file WebSocketServer.cpp
 * @author paul
 * @date 10.03.19
 * @brief WebSocketServer @TODO
 */

#include <iostream>
#include "WebSocketServer.hpp"

namespace network {
    AsyncCallList WebSocketServer::callList{std::make_shared<std::pair<std::list<std::function<void()>>,std::mutex>>()};
    int WebSocketServer::connectionUidCount{0};
    const util::Listener<std::shared_ptr<Connection>> WebSocketServer::connectionListener;
    std::map<int, std::shared_ptr<Connection>> WebSocketServer::connections;

    WebSocketServer::WebSocketServer(uint16_t port) :
        finished{false},
        context{nullptr, lws_context_destroy},
        protocols{
            {
                "http-only",
                &WebSocketServer::handler,
                sizeof(int),
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

            network::WebSocketServer::callList->second.lock();
            for (const auto &call : network::WebSocketServer::callList->first) {
                call();
            }
            network::WebSocketServer::callList->first.clear();
            network::WebSocketServer::callList->second.unlock();
        }
    }

    void WebSocketServer::sendImpl(std::string text, lws *wsi) {
        lws_write(wsi, reinterpret_cast<unsigned char*>(text.data()), text.length(), LWS_WRITE_TEXT);
    }

    WebSocketServer::~WebSocketServer() {
        finished = true;
        workerThread.join();
    }

    int WebSocketServer::handler(lws *websocket, lws_callback_reasons reasons, void *userData, void *data, size_t len) {
        auto *id = static_cast<int*>(userData);
        std::string text{static_cast<char *>(data), len};

        switch (reasons) {
            case LWS_CALLBACK_ESTABLISHED: {
                *id = ++connectionUidCount;
                auto connection = std::make_shared<Connection>(websocket, WebSocketServer::callList);
                connections.emplace(std::make_pair(*id, connection));
                WebSocketServer::connectionListener(connection);
                std::cout << "Established (" << *id << ")" << std::endl;
                break;
            }
            case LWS_CALLBACK_CLOSED: {
                std::cout << "Closed (" << *id << ")" << std::endl;
                connections.erase(*id);
                break;
            }
            case LWS_CALLBACK_RECEIVE: {
                std::cout << "Recv (" << *id << "): " << text << std::endl;
                auto it = connections.find(*id);
                if (it != connections.end()) {
                    it->second->receiveListener(text);
                }
                break;
            }
            default:
                break;
        }

        return 0;
    }

}
