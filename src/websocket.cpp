#include "websocket.hpp"

namespace kuzzleio {

    WebSocket::WebSocket(const std::string& host) {
      
    }

    void WebSocket::addListener(int, EventListener*) {}
    void WebSocket::removeListener(int, EventListener*) {}
    void WebSocket::removeAllListeners(int) {}
    void WebSocket::once(int, EventListener*) {}
    int WebSocket::listenerCount(int) {}
    void WebSocket::connect() {}
    std::string WebSocket::send(const std::string&, query_options *, kuzzle_response*, const std::string&) {}
    std::string WebSocket::close() {}
    int WebSocket::getState() {}
    void WebSocket::emitEvent(int, void*) {}
    void WebSocket::registerSub(const std::string&, const std::string&, const std::string&, int, NotificationListener*, void*) {}
    void WebSocket::unregisterSub(const std::string&) {}
    void WebSocket::cancelSubs() {}
    void WebSocket::startQueuing() {}
    void WebSocket::stopQueuing() {}
    void WebSocket::playQueue() {}
    void WebSocket::clearQueue() {}

}