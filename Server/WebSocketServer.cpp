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
        context{nullptr, lws_context_destroy} {

        std::vector<lws_protocols> protocols = {
            {
                "http-only",
                &WebSocketServer::handler,
                sizeof(Connection),
                4096,
                0,
                nullptr,
                0
            }
        };

        lws_context_creation_info contextCreationInfo{};
        contextCreationInfo.port = port;
        contextCreationInfo.protocols = protocols.data();
        //@TODO hopefully the data behind the pointer is copied, else we have a segfault later on
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

            this->toCallLock.lock();
            for (const auto &call : toCall) {
                call();
            }
            this->toCall.clear();
            this->toCallLock.unlock();
        }
    }

    void WebSocketServer::sendImpl(const std::string &text) {

    }

    WebSocketServer::~WebSocketServer() {
        finished = true;
        workerThread.join();
    }

    int
    WebSocketServer::handler(lws *websocket, lws_callback_reasons reasons, void *userData, void *data, size_t len) {
        auto *connection = static_cast<Connection*>(userData);

        switch (reasons) {
            case LWS_CALLBACK_PROTOCOL_INIT:break;
            case LWS_CALLBACK_PROTOCOL_DESTROY:break;
            case LWS_CALLBACK_WSI_CREATE:break;
            case LWS_CALLBACK_WSI_DESTROY:break;
            case LWS_CALLBACK_OPENSSL_LOAD_EXTRA_CLIENT_VERIFY_CERTS:break;
            case LWS_CALLBACK_OPENSSL_LOAD_EXTRA_SERVER_VERIFY_CERTS:break;
            case LWS_CALLBACK_OPENSSL_PERFORM_CLIENT_CERT_VERIFICATION:break;
            case LWS_CALLBACK_OPENSSL_CONTEXT_REQUIRES_PRIVATE_KEY:break;
            case LWS_CALLBACK_SSL_INFO:break;
            case LWS_CALLBACK_OPENSSL_PERFORM_SERVER_CERT_VERIFICATION:break;
            case LWS_CALLBACK_SERVER_NEW_CLIENT_INSTANTIATED:break;
            case LWS_CALLBACK_HTTP:break;
            case LWS_CALLBACK_HTTP_BODY:break;
            case LWS_CALLBACK_HTTP_BODY_COMPLETION:break;
            case LWS_CALLBACK_HTTP_FILE_COMPLETION:break;
            case LWS_CALLBACK_HTTP_WRITEABLE:break;
            case LWS_CALLBACK_CLOSED_HTTP:break;
            case LWS_CALLBACK_FILTER_HTTP_CONNECTION:break;
            case LWS_CALLBACK_ADD_HEADERS:break;
            case LWS_CALLBACK_CHECK_ACCESS_RIGHTS:break;
            case LWS_CALLBACK_PROCESS_HTML:break;
            case LWS_CALLBACK_HTTP_BIND_PROTOCOL:break;
            case LWS_CALLBACK_HTTP_DROP_PROTOCOL:break;
            case LWS_CALLBACK_HTTP_CONFIRM_UPGRADE:break;
            case LWS_CALLBACK_ESTABLISHED_CLIENT_HTTP:break;
            case LWS_CALLBACK_CLOSED_CLIENT_HTTP:break;
            case LWS_CALLBACK_RECEIVE_CLIENT_HTTP_READ:break;
            case LWS_CALLBACK_RECEIVE_CLIENT_HTTP:break;
            case LWS_CALLBACK_COMPLETED_CLIENT_HTTP:break;
            case LWS_CALLBACK_CLIENT_HTTP_WRITEABLE:break;
            case LWS_CALLBACK_CLIENT_HTTP_BIND_PROTOCOL:break;
            case LWS_CALLBACK_CLIENT_HTTP_DROP_PROTOCOL:break;
            case LWS_CALLBACK_ESTABLISHED:break;
            case LWS_CALLBACK_CLOSED:break;
            case LWS_CALLBACK_SERVER_WRITEABLE:break;
            case LWS_CALLBACK_RECEIVE:break;
            case LWS_CALLBACK_RECEIVE_PONG:break;
            case LWS_CALLBACK_WS_PEER_INITIATED_CLOSE:break;
            case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:break;
            case LWS_CALLBACK_CONFIRM_EXTENSION_OKAY:break;
            case LWS_CALLBACK_WS_SERVER_BIND_PROTOCOL:break;
            case LWS_CALLBACK_WS_SERVER_DROP_PROTOCOL:break;
            case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:break;
            case LWS_CALLBACK_CLIENT_FILTER_PRE_ESTABLISH:break;
            case LWS_CALLBACK_CLIENT_ESTABLISHED:break;
            case LWS_CALLBACK_CLIENT_CLOSED:break;
            case LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER:break;
            case LWS_CALLBACK_CLIENT_RECEIVE:break;
            case LWS_CALLBACK_CLIENT_RECEIVE_PONG:break;
            case LWS_CALLBACK_CLIENT_WRITEABLE:break;
            case LWS_CALLBACK_CLIENT_CONFIRM_EXTENSION_SUPPORTED:break;
            case LWS_CALLBACK_WS_EXT_DEFAULTS:break;
            case LWS_CALLBACK_FILTER_NETWORK_CONNECTION:break;
            case LWS_CALLBACK_WS_CLIENT_BIND_PROTOCOL:break;
            case LWS_CALLBACK_WS_CLIENT_DROP_PROTOCOL:break;
            case LWS_CALLBACK_GET_THREAD_ID:break;
            case LWS_CALLBACK_ADD_POLL_FD:break;
            case LWS_CALLBACK_DEL_POLL_FD:break;
            case LWS_CALLBACK_CHANGE_MODE_POLL_FD:break;
            case LWS_CALLBACK_LOCK_POLL:break;
            case LWS_CALLBACK_UNLOCK_POLL:break;
            case LWS_CALLBACK_CGI:break;
            case LWS_CALLBACK_CGI_TERMINATED:break;
            case LWS_CALLBACK_CGI_STDIN_DATA:break;
            case LWS_CALLBACK_CGI_STDIN_COMPLETED:break;
            case LWS_CALLBACK_CGI_PROCESS_ATTACH:break;
            case LWS_CALLBACK_SESSION_INFO:break;
            case LWS_CALLBACK_GS_EVENT:break;
            case LWS_CALLBACK_HTTP_PMO:break;
            case LWS_CALLBACK_RAW_PROXY_CLI_RX:break;
            case LWS_CALLBACK_RAW_PROXY_SRV_RX:break;
            case LWS_CALLBACK_RAW_PROXY_CLI_CLOSE:break;
            case LWS_CALLBACK_RAW_PROXY_SRV_CLOSE:break;
            case LWS_CALLBACK_RAW_PROXY_CLI_WRITEABLE:break;
            case LWS_CALLBACK_RAW_PROXY_SRV_WRITEABLE:break;
            case LWS_CALLBACK_RAW_PROXY_CLI_ADOPT:break;
            case LWS_CALLBACK_RAW_PROXY_SRV_ADOPT:break;
            case LWS_CALLBACK_RAW_PROXY_CLI_BIND_PROTOCOL:break;
            case LWS_CALLBACK_RAW_PROXY_SRV_BIND_PROTOCOL:break;
            case LWS_CALLBACK_RAW_PROXY_CLI_DROP_PROTOCOL:break;
            case LWS_CALLBACK_RAW_PROXY_SRV_DROP_PROTOCOL:break;
            case LWS_CALLBACK_RAW_RX:break;
            case LWS_CALLBACK_RAW_CLOSE:break;
            case LWS_CALLBACK_RAW_WRITEABLE:break;
            case LWS_CALLBACK_RAW_ADOPT:break;
            case LWS_CALLBACK_RAW_SKT_BIND_PROTOCOL:break;
            case LWS_CALLBACK_RAW_SKT_DROP_PROTOCOL:break;
            case LWS_CALLBACK_RAW_ADOPT_FILE:break;
            case LWS_CALLBACK_RAW_RX_FILE:break;
            case LWS_CALLBACK_RAW_WRITEABLE_FILE:break;
            case LWS_CALLBACK_RAW_CLOSE_FILE:break;
            case LWS_CALLBACK_RAW_FILE_BIND_PROTOCOL:break;
            case LWS_CALLBACK_RAW_FILE_DROP_PROTOCOL:break;
            case LWS_CALLBACK_TIMER:break;
            case LWS_CALLBACK_EVENT_WAIT_CANCELLED:break;
            case LWS_CALLBACK_CHILD_CLOSING:break;
            case LWS_CALLBACK_VHOST_CERT_AGING:break;
            case LWS_CALLBACK_VHOST_CERT_UPDATE:break;
            case LWS_CALLBACK_USER:break;
        }

        return 0;
    }
}
