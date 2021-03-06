#ifndef KUZZLE_WEBSOCKET_HPP
#define KUZZLE_WEBSOCKET_HPP

#include "internal/options.hpp"
#include "internal/core.hpp"
#include "protocol.hpp"

namespace kuzzleio {
  class WebSocket : public Protocol {
    private:
      web_socket* _web_socket;

    public:
      WebSocket(const std::string& host);
      WebSocket(const std::string& host, const Options& options);
      virtual ~WebSocket();

      virtual KuzzleEventEmitter* addListener(
          Event, SharedEventListener) noexcept override;
      virtual KuzzleEventEmitter* removeListener(
          Event, SharedEventListener) noexcept override;
      virtual KuzzleEventEmitter* removeAllListeners(Event) noexcept override;
      virtual KuzzleEventEmitter* once(
          Event, SharedEventListener) noexcept override;

      virtual void notify(notification_result* payload) noexcept override;

      virtual void connect() override;
      virtual kuzzle_response* send(const std::string&, query_options *,
          const std::string&) override;
      virtual void close() override;
      virtual int getState() override;
      virtual void registerSub(
          const std::string& channel, const std::string& room_id,
          const std::string& filters, bool subscribe_to_self,
          std::shared_ptr<NotificationListener>) override;
      virtual void unregisterSub(const std::string&) override;
      virtual void cancelSubs() override;
      virtual std::string getHost() override;
      virtual bool isReady() override;

      // Getters
      unsigned int getPort();
      bool isSslConnection();
  };

}

#endif
