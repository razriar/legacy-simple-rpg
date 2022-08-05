#pragma once

#include <any>
#include <vector>

#include "bll/property.h"
#include "condition.h"
#include "query.h"

namespace bll {
template <class Object>
class ExistanceQuery : public Query<Object> {
   private:
    std::vector<Condition> conditions_;

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
};
}  // namespace bll
