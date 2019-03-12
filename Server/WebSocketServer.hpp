/**
 * @file WebSocketServer.hpp
 * @author paul
 * @date 10.03.19
 * @brief WebSocketServer @TODO
 */

#ifndef SOPRANETWORK_WEBSOCKETSERVER_HPP
#define SOPRANETWORK_WEBSOCKETSERVER_HPP

#include <cstdint>
#include <thread>
#include <mutex>
#include <atomic>
#include <map>

#include <libwebsockets.h>

#include "Listener.hpp"
#include "Connection.hpp"

namespace network {
    class WebSocketServer {
        friend class Connection;
    public:
        explicit WebSocketServer(uint16_t port);

        static const util::Listener<std::shared_ptr<Connection>> connectionListener;

        ~WebSocketServer();
    private:
        void run();

        std::thread workerThread;
        std::atomic_bool finished;

        std::unique_ptr<lws_context, decltype(&lws_context_destroy)> context;
        const std::vector<lws_protocols> protocols;

        static void sendImpl(std::string text, lws *wsi);
        static int handler(lws *websocket, lws_callback_reasons reasons, void * userData, void *data,
                std::size_t len);
        static int connectionUidCount;
        static AsyncCallList callList;
        static std::map<int, std::shared_ptr<Connection>> connections;
    };

}

#endif //SOPRANETWORK_WEBSOCKETSERVER_HPP