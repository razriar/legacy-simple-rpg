#pragma once

#include <any>
#include <string>
#include <vector>

#include "bll/metadata.h"
#include "bll/property.h"
#include "query.h"

namespace bll {
struct Column {
    std::string name;
    std::any value;
};
template <class Object>
class CreationQuery : public Query<Object> {
   private:
    std::vector<Column> columns_;

   public:
    template <OwnedBy<Object> OwnedProperty>
    void Add(typename OwnedProperty::ValueType value) {
        auto name = Metadata<OwnedProperty>::ColumnName();
        if (!name)
            throw std::invalid_argument("Queried property has no metadata");
        Column column = { *name, value };
        columns_.push_back(column);
    }
    std::vector<Column> columns() { return columns_; }
};
}  // namespace bll
