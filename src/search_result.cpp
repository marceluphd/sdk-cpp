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
    SearchResult::SearchResult(search_result* sr) {
        _sr = sr;

        aggregations = std::string(_sr->aggregations);
        hits = std::string(_sr->hits);
        total = _sr->total;
        fetched = _sr->fetched;
        scroll_id = std::string(_sr->scroll_id);
    }

    SearchResult::~SearchResult() {
        kuzzle_free_search_result(_sr);
    }

    SearchResult* SearchResult::next() {
        search_result *sr = kuzzle_document_search_next(_sr);
        return new SearchResult(sr);
    }
}