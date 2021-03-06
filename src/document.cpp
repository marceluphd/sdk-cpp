// Copyright 2015-2018 Kuzzle
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "kuzzle.hpp"
#include "internal/document.hpp"
#include "internal/search_result.hpp"

namespace kuzzleio {
  Document::Document(kuzzle* kuzzle) {
    _document = kuzzle_get_document_controller(kuzzle);
    kuzzle_new_document(_document);
  }

  Document::~Document() {
    unregisterDocument(_document);

    // do not use "delete":
    // _document is allocated in the cgo world, using calloc
    free(_document);
  }

  int Document::count(const std::string& index, const std::string& collection) {
    return this->count(index, collection, query_options());
  }

  int Document::count(const std::string& index, const std::string& collection, const query_options& options) {
    return this->count(index, collection, "{}", options);
  }

  int Document::count(const std::string& index, const std::string& collection, const std::string& query) {
    return this->count(index, collection, query, query_options());
  }

  int Document::count(const std::string& index, const std::string& collection, const std::string& query, const query_options& options) {
    KUZZLE_API(int_result, r, kuzzle_document_count(
      _document,
      const_cast<char*>(index.c_str()),
      const_cast<char*>(collection.c_str()),
      const_cast<char*>(query.c_str()),
      const_cast<query_options*>(&options)))

    int ret = r->result;
    kuzzle_free_int_result(r);

    return ret;
  }


  bool Document::exists(const std::string& index, const std::string& collection, const std::string& id) {
    return this->exists(index, collection, id, query_options());
  }

  bool Document::exists(const std::string& index, const std::string& collection, const std::string& id, const query_options& options) {
    KUZZLE_API(bool_result, r, kuzzle_document_exists(
      _document,
      const_cast<char*>(index.c_str()),
      const_cast<char*>(collection.c_str()),
      const_cast<char*>(id.c_str()),
      const_cast<query_options*>(&options)))

    bool ret = r->result;
    kuzzle_free_bool_result(r);

    return ret;
  }


  std::string Document::create(const std::string& index, const std::string& collection, const std::string& id, const std::string& document) {
    return this->create(index, collection, id, document, query_options());
  }

  std::string Document::create(const std::string& index, const std::string& collection, const std::string& id, const std::string& document, const query_options& options) {
    KUZZLE_API(string_result, r, kuzzle_document_create(
      _document,
      const_cast<char*>(index.c_str()),
      const_cast<char*>(collection.c_str()),
      const_cast<char*>(id.c_str()),
      const_cast<char*>(document.c_str()),
      const_cast<query_options*>(&options)))

    std::string ret = r->result;
    kuzzle_free_string_result(r);

    return ret;
  }


  std::string Document::createOrReplace(const std::string& index, const std::string& collection, const std::string& id, const std::string& document) {
    return this->createOrReplace(index, collection, id, document, query_options());
  }

  std::string Document::createOrReplace(const std::string& index, const std::string& collection, const std::string& id, const std::string& document, const query_options& options) {
    KUZZLE_API(string_result, r, kuzzle_document_create_or_replace(
      _document,
      const_cast<char*>(index.c_str()),
      const_cast<char*>(collection.c_str()),
      const_cast<char*>(id.c_str()),
      const_cast<char*>(document.c_str()),
      const_cast<query_options*>(&options)))

    std::string ret = r->result;
    kuzzle_free_string_result(r);

    return ret;
  }


  std::string Document::delete_(const std::string& index, const std::string& collection, const std::string& id) {
    return this->delete_(index, collection, id, query_options());
  }

  std::string Document::delete_(const std::string& index, const std::string& collection, const std::string& id, const query_options& options) {
    KUZZLE_API(string_result, r, kuzzle_document_delete(
      _document,
      const_cast<char*>(index.c_str()),
      const_cast<char*>(collection.c_str()),
      const_cast<char*>(id.c_str()),
      const_cast<query_options*>(&options)))

    std::string ret = r->result;
    kuzzle_free_string_result(r);

    return ret;
  }


  std::vector<std::string> Document::deleteByQuery(const std::string& index, const std::string& collection, const std::string& query) {
    return this->deleteByQuery(index, collection, query, query_options());
  }

  std::vector<std::string> Document::deleteByQuery(const std::string& index, const std::string& collection, const std::string& query, const query_options& options) {
    KUZZLE_API(string_array_result, r, kuzzle_document_delete_by_query(
      _document,
      const_cast<char*>(index.c_str()),
      const_cast<char*>(collection.c_str()),
      const_cast<char*>(query.c_str()),
      const_cast<query_options*>(&options)))

    std::vector<std::string> v = std::vector<std::string>(r->result, r->result + r->result_length);
    kuzzle_free_string_array_result(r);

    return v;
  }


  std::string Document::get(const std::string& index, const std::string& collection, const std::string& id) {
    return this->get(index, collection, id, query_options());
  }

  std::string Document::get(const std::string& index, const std::string& collection, const std::string& id, const query_options& options) {
    KUZZLE_API(string_result, r, kuzzle_document_get(
      _document,
      const_cast<char*>(index.c_str()),
      const_cast<char*>(collection.c_str()),
      const_cast<char*>(id.c_str()),
      const_cast<query_options*>(&options)))

    std::string ret = r->result;
    kuzzle_free_string_result(r);

    return ret;
  }


  std::string Document::replace(const std::string& index, const std::string& collection, const std::string& id, const std::string& document) {
    return this->replace(index, collection, id, document, query_options());
  }

  std::string Document::replace(const std::string& index, const std::string& collection, const std::string& id, const std::string& document, const query_options& options) {
    KUZZLE_API(string_result, r, kuzzle_document_replace(
      _document,
      const_cast<char*>(index.c_str()),
      const_cast<char*>(collection.c_str()),
      const_cast<char*>(id.c_str()),
      const_cast<char*>(document.c_str()),
      const_cast<query_options*>(&options)))

    std::string ret = r->result;
    kuzzle_free_string_result(r);

    return ret;
  }


  std::string Document::update(const std::string& index, const std::string& collection, const std::string& id, const std::string& document) {
    return this->update(index, collection, id, document, query_options());
  }

  std::string Document::update(const std::string& index, const std::string& collection, const std::string& id, const std::string& document, const query_options& options) {
    KUZZLE_API(string_result, r, kuzzle_document_update(
      _document,
      const_cast<char*>(index.c_str()),
      const_cast<char*>(collection.c_str()),
      const_cast<char*>(id.c_str()),
      const_cast<char*>(document.c_str()),
      const_cast<query_options*>(&options)))

    std::string ret = r->result;
    kuzzle_free_string_result(r);

    return ret;
  }


  bool Document::validate(const std::string& index, const std::string& collection, const std::string& document) {
    return this->validate(index, collection, document, query_options());
  }

  bool Document::validate(const std::string& index, const std::string& collection, const std::string& document, const query_options& options) {
    KUZZLE_API(bool_result, r, kuzzle_document_validate(
      _document,
      const_cast<char*>(index.c_str()),
      const_cast<char*>(collection.c_str()),
      const_cast<char*>(document.c_str()),
      const_cast<query_options*>(&options)))

    bool ret = r->result;
    kuzzle_free_bool_result(r);

    return ret;
  }

  std::shared_ptr<SearchResult> Document::search(
      const std::string& index,
      const std::string& collection,
      const std::string& query) {
    return this->search(index, collection, query, query_options());
  }

  std::shared_ptr<SearchResult> Document::search(
      const std::string& index,
      const std::string& collection,
      const std::string& query,
      const query_options& options) {
    KUZZLE_API(
        search_result,
        r,
        kuzzle_document_search(_document, const_cast<char*>(index.c_str()),
                               const_cast<char*>(collection.c_str()),
                               const_cast<char*>(query.c_str()),
                               const_cast<query_options*>(&options)))

    if (r == nullptr) {
      return nullptr;
    }

    return std::make_shared<SearchResult>(r);
  }


  std::string Document::mCreate(const std::string& index, const std::string& collection, const std::string& documents) {
    return this->mCreate(index, collection, documents, query_options());
  }

  std::string Document::mCreate(const std::string& index, const std::string& collection, const std::string& documents, const query_options& options) {
    KUZZLE_API(string_result, r, kuzzle_document_mcreate(
      _document,
      const_cast<char*>(index.c_str()),
      const_cast<char*>(collection.c_str()),
      const_cast<char*>(documents.c_str()),
      const_cast<query_options*>(&options)))

    std::string ret = r->result;
    kuzzle_free_string_result(r);

    return ret;
  }


  std::string Document::mCreateOrReplace(const std::string& index, const std::string& collection, const std::string& documents) {
    return this->mCreateOrReplace(index, collection, documents, query_options());
  }

  std::string Document::mCreateOrReplace(const std::string& index, const std::string& collection, const std::string& documents, const query_options& options) {
    KUZZLE_API(string_result, r, kuzzle_document_mcreate_or_replace(
      _document,
      const_cast<char*>(index.c_str()),
      const_cast<char*>(collection.c_str()),
      const_cast<char*>(documents.c_str()),
      const_cast<query_options*>(&options)))

    std::string ret = r->result;
    kuzzle_free_string_result(r);
    return ret;
  }


  std::vector<std::string> Document::mDelete(const std::string& index, const std::string& collection, const std::vector<std::string>& ids) {
    return this->mDelete(index, collection, ids, query_options());
  }

  std::vector<std::string> Document::mDelete(const std::string& index, const std::string& collection, const std::vector<std::string>& ids, const query_options& options) {
    char **ids_array = new char *[ids.size()];

    for (size_t i = 0; i < ids.size(); i++) {
      ids_array[i] = const_cast<char*>(ids[i].c_str());
    }

    KUZZLE_API(
      string_array_result,
      r,
      kuzzle_document_mdelete(_document,
        const_cast<char*>(index.c_str()),
        const_cast<char*>(collection.c_str()),
        ids_array,
        ids.size(),
        const_cast<query_options*>(&options)),
      delete[] ids_array)

    std::vector<std::string> v = std::vector<std::string>(r->result, r->result + r->result_length);
    kuzzle_free_string_array_result(r);

    return v;
  }


  std::string Document::mGet(const std::string& index, const std::string& collection, const std::vector<std::string>& ids) {
    return this->mGet(index, collection, ids, query_options());
  }

  std::string Document::mGet(const std::string& index, const std::string& collection, const std::vector<std::string>& ids, const query_options& options) {
    char **ids_array = new char *[ids.size()];

    for (size_t i = 0; i < ids.size(); i++) {
      ids_array[i] = const_cast<char*>(ids[i].c_str());
    }

    KUZZLE_API(
      string_result,
      r,
      kuzzle_document_mget(
        _document,
        const_cast<char*>(index.c_str()),
        const_cast<char*>(collection.c_str()),
        ids_array,
        ids.size(),
        const_cast<query_options*>(&options)),
      delete[] ids_array)

    std::string ret = r->result;
    kuzzle_free_string_result(r);

    return ret;
  }


  std::string Document::mReplace(const std::string& index, const std::string& collection, const std::string& documents) {
    return this->mReplace(index, collection, documents, query_options());
  }

  std::string Document::mReplace(const std::string& index, const std::string& collection, const std::string& documents, const query_options& options) {
    KUZZLE_API(string_result, r, kuzzle_document_mreplace(
      _document,
      const_cast<char*>(index.c_str()),
      const_cast<char*>(collection.c_str()),
      const_cast<char*>(documents.c_str()),
      const_cast<query_options*>(&options)))

    std::string ret = r->result;
    kuzzle_free_string_result(r);

    return ret;
  }


  std::string Document::mUpdate(const std::string& index, const std::string& collection, const std::string& documents) {
    return this->mUpdate(index, collection, documents, query_options());
  }

  std::string Document::mUpdate(const std::string& index, const std::string& collection, const std::string& documents, const query_options& options) {
    KUZZLE_API(string_result, r, kuzzle_document_mupdate(
      _document,
      const_cast<char*>(index.c_str()),
      const_cast<char*>(collection.c_str()),
      const_cast<char*>(documents.c_str()),
      const_cast<query_options*>(&options)))

    std::string ret = r->result;
    kuzzle_free_string_result(r);

    return ret;
  }
}
