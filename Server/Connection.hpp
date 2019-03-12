/**
 * @file ConnectionInformation.hpp
 * @author paul
 * @date 10.03.19
 * @brief ConnectionInformation @TODO
 */

#ifndef SOPRANETWORK_CONNECTIONINFORMATION_HPP
#define SOPRANETWORK_CONNECTIONINFORMATION_HPP

#include "Listener.hpp"

namespace network {
    class Connection {
        public:
            void send(const std::string &text);

            const util::Listener<std::string> receiveListener;
    };
}

#endif //SOPRANETWORK_CONNECTIONINFORMATION_HPP
