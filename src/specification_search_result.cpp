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

namespace kuzzleio {
    SpecificationSearchResult::SpecificationSearchResult(search_result *sr) : SearchResult(sr) {
    }
    SpecificationSearchResult::~SpecificationSearchResult() {
        kuzzle_free_search_result(_sr);
    }

    SpecificationSearchResult* SpecificationSearchResult::next() {
        search_result *sr = kuzzle_collection_search_specifications_next(_sr);
        return new SpecificationSearchResult(sr);
    }



}