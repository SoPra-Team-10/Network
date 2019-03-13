/**
 * @file ConnectionInformation.hpp
 * @author paul
 * @date 10.03.19
 * @brief ConnectionInformation @TODO
 */

#ifndef SOPRANETWORK_CONNECTIONINFORMATION_HPP
#define SOPRANETWORK_CONNECTIONINFORMATION_HPP

#include <memory>
#include <mutex>

#include <libwebsockets.h>

#include "Listener.hpp"

namespace network {
    using AsyncCallList = std::shared_ptr<std::pair<std::list<std::function<void()>>, std::mutex>>;

    class Connection {
        friend class WebSocketServer;
        public:
            Connection() = delete;
            const util::Listener<std::string> receiveListener;
            void send(std::string text);
        private:
            Connection(lws* socket, AsyncCallList asyncCallList);
            lws* socket;
            AsyncCallList callList;
    };
}

#endif //SOPRANETWORK_CONNECTIONINFORMATION_HPP
