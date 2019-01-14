#include "steps.hpp"

#include <signal.h>

CustomNotificationListener* CustomNotificationListener::_singleton;

// Anonymous namespace to handle a linker error
// see https://stackoverflow.com/questions/14320148/linker-error-on-cucumber-cpp-when-dealing-with-multiple-feature-files
namespace {

  GIVEN("^I subscribe to \'(.*)\'$") {
    REGEX_PARAM(std::string, collection_id);

    ScenarioScope<KuzzleCtx> ctx;

    try {
      CustomNotificationListener *l = CustomNotificationListener::getSingleton();
      ctx->room_id = ctx->kuzzle->realtime->subscribe(ctx->index, collection_id, "{}", &l->listener);
    } catch (KuzzleException e) {
      BOOST_FAIL(e.what());
    }
  }

  WHEN("^I create a document in \'([^\"]*)\'$") {
    REGEX_PARAM(std::string, collection_id);

    ScenarioScope<KuzzleCtx> ctx;

    query_options options;
    options.refresh = const_cast<char*>("wait_for");

    try {
      ctx->kuzzle->document->create(ctx->index, ctx->collection, "", R"({"foo":"bar"})", options);
    } catch (KuzzleException e) {
      BOOST_FAIL(e.what());
    }
  }

  THEN("^I receive a notification$") {
    ScenarioScope<KuzzleCtx> ctx;

    sleep(1);
    BOOST_CHECK(ctx->notif_result != nullptr);
    ctx->kuzzle->realtime->unsubscribe(ctx->room_id);

    delete ctx->notif_result;
    ctx->notif_result = nullptr;
  }

  GIVEN("^I subscribe to \'([^\"]*)\' with \'(.*)\' as filter$") {
    REGEX_PARAM(std::string, collection_id);
    REGEX_PARAM(std::string, filter);

    ScenarioScope<KuzzleCtx> ctx;

    try {
      CustomNotificationListener *l = CustomNotificationListener::getSingleton();
      ctx->kuzzle->realtime->subscribe(ctx->index, collection_id, filter, &l->listener);
    } catch (KuzzleException e) {
      BOOST_FAIL(e.what());
    }
  }

  WHEN("^I update the document with id \'([^\"]*)\' and content \'([^\"]*)\' = \'([^\"]*)\'$") {
    REGEX_PARAM(std::string, document_id);
    REGEX_PARAM(std::string, key);
    REGEX_PARAM(std::string, value);

    ScenarioScope<KuzzleCtx> ctx;

    query_options options;
    options.refresh = const_cast<char*>("wait_for");

    try {
      ctx->kuzzle->document->update(ctx->index, ctx->collection, document_id, "{\""+key+"\":\""+value+"\"}", options);
    } catch (KuzzleException e) {
      BOOST_FAIL(e.what());
    }
  }

  WHEN("^I delete the document with id \'([^\"]*)\'$") {
    REGEX_PARAM(std::string, document_id);

    ScenarioScope<KuzzleCtx> ctx;

    try {
      ctx->kuzzle->document->delete_(ctx->index, ctx->collection, document_id);
      ctx->success = 1;
    } catch (KuzzleException e) {
      BOOST_FAIL(e.what());
    }
  }

  WHEN("^I publish a document$") {
    ScenarioScope<KuzzleCtx> ctx;

    try {
      ctx->kuzzle->realtime->publish(ctx->index, ctx->collection, "{}");
    } catch (KuzzleException e) {
      BOOST_FAIL(e.what());
    }
  }

  GIVEN("^I unsubscribe$") {
    ScenarioScope<KuzzleCtx> ctx;

    try {
      ctx->kuzzle->realtime->unsubscribe(ctx->room_id);
      ctx->notif_result = NULL;
    } catch (KuzzleException e) {
      BOOST_FAIL(e.what());
    }
  }

  THEN("^I do not receive a notification$") {
    ScenarioScope<KuzzleCtx> ctx;

    BOOST_CHECK(ctx->notif_result == NULL);
  }
}
