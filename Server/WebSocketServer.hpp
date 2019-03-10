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

class WebSocketServer {
public:
    explicit WebSocketServer(uint16_t port);
    void send(std::string text);
    const util::Listener<std::string> receiveListener;

private:
    void sendImpl(std::string text);
    static int callBackHttp(lws_context*, lws*, lws_callback_reasons, void*,void*,std::size_t);

    std::thread workerThread;
    std::list<std::function<void()>> toCall;
    std::mutex toCallLock;


};


#endif //SOPRANETWORK_WEBSOCKETSERVER_HPP
