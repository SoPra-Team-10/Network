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

    /**
     * A connection represents one client of the server. This class cannot be instantiated,
     * all instances get created by a WebSocketServer.
     */
    class Connection {
        friend class WebSocketServer;
        public:
            /**
             * CTor: Not default constructable
             */
            Connection() = delete;

            /**
             * Listener which is called every time a new message is received.
             */
            const util::Listener<std::string> receiveListener;

            /**
             * Send a string to the client. The data is not send immediatly but when the server thread
             * is not busy (should be usually less than 50ms)
             * @param text the text to send
             */
            void send(std::string text);
        private:
            Connection(lws* socket, AsyncCallList asyncCallList);
            lws* socket;
            AsyncCallList callList;
    };
}

#endif //SOPRANETWORK_CONNECTIONINFORMATION_HPP
