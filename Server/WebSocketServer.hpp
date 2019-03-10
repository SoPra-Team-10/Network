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
#include <libwebsockets.h>
#include "../Util/Listener.hpp"

namespace network {
    class WebSocketServer {
    public:
        explicit WebSocketServer(uint16_t port);

        void send(const std::string &text);

        const util::Listener<std::string> receiveListener;

    private:
        void sendImpl(const std::string &text);
        void run();

        std::thread workerThread;
        std::list<std::function<void()>> toCall;
        std::mutex toCallLock;

        std::unique_ptr<lws_context, decltype(&lws_context_destroy)> context;

        static int callBackHttp(lws *, lws_callback_reasons, void *, void *, std::size_t);
        static int callBackOther(lws *, lws_callback_reasons, void *, void *, std::size_t);
        static lws_protocols protocols[];
    };
}

#endif //SOPRANETWORK_WEBSOCKETSERVER_HPP
