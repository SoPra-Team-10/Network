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
#include <atomic>
#include <map>

#include <libwebsockets.h>

#include "Listener.hpp"
#include "Connection.hpp"

namespace network {
    class WebSocketServer {
        friend class Connection;
    public:
        WebSocketServer(uint16_t port, const std::string &protocolName);

        const util::Listener<std::shared_ptr<Connection>> connectionListener;

        ~WebSocketServer();
    private:
        void run();
        int handler(lws *websocket, lws_callback_reasons reasons, int *id, std::string text);

        std::thread workerThread;
        std::atomic_bool finished;

        std::string protocolName;
        std::unique_ptr<lws_context, decltype(&lws_context_destroy)> context;
        const std::vector<lws_protocols> protocols;

        AsyncCallList callList;
        int connectionUidCount;
        std::map<int, std::shared_ptr<Connection>> connections;

        static int globalHandler(lws *websocket, lws_callback_reasons reasons, void *userData, void *data,
                                 std::size_t len);
        static std::map<lws_context*, WebSocketServer*> instances;
        static void sendImpl(std::string text, lws *wsi);
    };

}

#endif //SOPRANETWORK_WEBSOCKETSERVER_HPP