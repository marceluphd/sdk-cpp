// Copyright 2015-2018 Kuzzle
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _KUZZLE_HPP_
#define _KUZZLE_HPP_

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <functional>

#include "internal/options.hpp"
#include "internal/exceptions.hpp"
#include "internal/core.hpp"
#include "internal/event_emitter.hpp"

#include "internal/realtime.hpp"
#include "internal/auth.hpp"
#include "internal/index.hpp"
#include "internal/server.hpp"
#include "internal/collection.hpp"
#include "internal/document.hpp"
#include "protocol.hpp"

#include "internal/search_result.hpp"
#include "internal/user_right.hpp"
#include "internal/user.hpp"

/*
 * Macro used by controller actions.
 * This standardizes and DRYifies the following process, making sure
 * that the underlying API result structure is correctly
 * freed when an error is received and when an exception
 * has to be thrown:
 *
 * - call the <_call> function, usually a kuzzle cgo function (with args)
 * - stores the result in a <_type> variable of name <_name>
 * - if an error has been received:
 *   - create an exception
 *   - free the result structure
 *   - throw the exception
 *
 * The last variadic parameter is a single line of code to be called
 * after the API result has been received, but before the error handling.
 * This is usually used to free intermediate variables instantiated to
 * convert a C++ arg into a cgo-compatible one
 */
#define KUZZLE_API(_type, _name, _call, ... ) \
  _type * _name = _call; \
  __VA_ARGS__; \
  if (_name != nullptr && _name->error != nullptr) {\
    int status = _name->status; \
    std::string err = _name->error; \
    kuzzle_free_##_type(_name); \
    throwKuzzleException(status, err); \
  }

namespace kuzzleio {
  class Collection;
  class Document;
  class Auth;
  class Index;
  class Server;
  class Realtime;
  class Protocol;

  class Kuzzle : public KuzzleEventEmitter {
    private:
      std::map<int, EventListener*>  _listener_instances;
      Protocol *_cpp_protocol;

    public:
      kuzzle *_kuzzle;
      protocol *_protocol;
      Auth *auth;
      Index *index;
      Server *server;
      Collection *collection;
      Document *document;
      Realtime *realtime;


      Kuzzle(Protocol* protocol);
      Kuzzle(Protocol* protocol, Options& options);
      virtual ~Kuzzle();

      void connect();
      void disconnect() noexcept;
      void emitEvent(Event event, const std::string& payload) noexcept;
      kuzzle_response* query(const kuzzle_request& request);
      kuzzle_response* query(const kuzzle_request& request, const query_options& options);

      // Offline queue
      Kuzzle* startQueuing() noexcept;
      Kuzzle* stopQueuing() noexcept;
      Kuzzle* playQueue() noexcept;
      Kuzzle* flushQueue() noexcept;

      // Setters
      Kuzzle* setAutoReplay(bool value) noexcept;
      Kuzzle* setVolatile(const std::string& volatile_data) noexcept;

      // Getters
      Protocol* getProtocol() noexcept;
      std::string getJwt() noexcept;
      std::string getVolatile() noexcept;
      std::map<int, EventListener*> getListeners() noexcept;

      // KuzzleEventEmitter implementation
      virtual int listenerCount(Event event) override;
      virtual KuzzleEventEmitter* addListener(Event event, EventListener* listener) override;
      virtual KuzzleEventEmitter* removeListener(Event event, EventListener* listener) override;
      virtual KuzzleEventEmitter* removeAllListeners(Event event) override;
      virtual KuzzleEventEmitter* once(Event event, EventListener* listener) override;
  };
}

#endif
