/**
 * @file WebSocketClient.hpp
 * @author paul
 * @date 13.03.19
 * @brief WebSocketClient @TODO
 */

#ifndef SOPRANETWORK_WEBSOCKETCLIENT_HPP
#define SOPRANETWORK_WEBSOCKETCLIENT_HPP

#include <string>
#include <thread>
#include <atomic>
#include <map>
#include <mutex>

#include <libwebsockets.h>

#include "Listener.hpp"

namespace network {
    using AsyncCallList = std::pair<std::list<std::function<void()>>, std::mutex>;

    class WebSocketClient {
    public:
        WebSocketClient(const std::string &server, const std::string &path,
                uint16_t port, const std::string &protocolName);
        const util::Listener<std::string> receiveListener;
        void send(std::string text);
        ~WebSocketClient();
    private:
        void run();
        int handler(lws *websocket, lws_callback_reasons reasons, std::string text);
        void connect();

        std::thread workerThread;
        std::atomic_bool finished;

        std::string server, path;
        uint16_t port;

        std::string protocolName;
        std::unique_ptr<lws_context, decltype(&lws_context_destroy)> context;
        lws *wsi;
        const std::vector<lws_protocols> protocols;

        AsyncCallList callList;

        static int globalHandler(lws *websocket, lws_callback_reasons reasons, void*, void *data,
                                 std::size_t len);
        static void sendImpl(std::string text, lws *wsi);
        static std::map<lws_context*, WebSocketClient*> instances;
    };
}


#endif //SOPRANETWORK_WEBSOCKETCLIENT_HPP
