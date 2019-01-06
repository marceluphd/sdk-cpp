// Copyright 2015-2018 Kuzzle
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// 		http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "internal/search_result.hpp"
#include "internal/core.hpp"

namespace kuzzleio {
    SearchResult::SearchResult(const search_result* sr)
      : _sr(sr),
        _aggregations(std::string(_sr->aggregations)),
        _hits(std::string(_sr->hits)),
        _total(_sr->total),
        _fetched(_sr->fetched),
        _scroll_id(std::string(_sr->scroll_id))
    {
    }

    SearchResult::~SearchResult() {
        kuzzle_free_search_result(const_cast<search_result*>(_sr));
    }

    SearchResult* SearchResult::next() const {
        search_result *sr = kuzzle_document_search_next(const_cast<search_result*>(_sr));
        return new SearchResult(sr);
    }

    size_t SearchResult::total() const {
      return _total;
    }

    size_t SearchResult::fetched() const {
      return _fetched;
    }

    const std::string& SearchResult::aggregations() const {
      return _aggregations;
    }

    const std::string& SearchResult::hits() const {
      return _hits;
    }

    const std::string& SearchResult::scroll_id() const {
      return _scroll_id;
    }
}
