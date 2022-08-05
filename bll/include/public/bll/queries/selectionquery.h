#pragma once

#include <vector>

#include "bll/property.h"
#include "condition.h"
#include "query.h"

namespace bll {
template <class Object>
class SelectionQuery : public Query<Object> {
   private:
    std::vector<Condition> conditions_;
    std::vector<std::string> fields_;

   public:
    template <OwnedBy<Object> OwnedProperty>
    void Require(Comparator comparator,
                 typename OwnedProperty::ValueType value) {
        auto column = Metadata<OwnedProperty>::ColumnName();
        if (!column)
            throw std::invalid_argument("Queried property has no metadata");
        Condition condition = {*column, comparator, value};
        conditions_.push_back(condition);
    }
    std::vector<Condition> conditions() { return conditions_; }
    template <OwnedBy<Object> OwnedProperty>
    void Field() {
        auto column = Metadata<OwnedProperty>::ColumnName();
        if (!column)
            throw std::invalid_argument("Queried property has no metadata");
        fields_.push_back(*column);
    }
    std::vector<std::string> fields() { return fields_; }
};
}  // namespace bll
