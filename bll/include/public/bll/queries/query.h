#pragma once

#include <map>
#include <string>
#include <type_traits>

#include "bll/metadata.h"

namespace bll {
template <typename Object>
class Query {
   private:
    std::string table_;

   public:
    Query() {
        auto table = Metadata<Object>::TableName();
        if (!table)
            throw std::invalid_argument("Queried object has no metadata");
        table_ = *table;
    }
    std::string table() {
        return table_;
    }
};
}  // namespace bll
