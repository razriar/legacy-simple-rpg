#pragma once

#include <any>
#include <vector>

#include "bll/property.h"
#include "query.h"

namespace bll {
enum Comparator {
    Equal = 0,
};
struct Condition {
    std::string column;
    Comparator comparator;
    std::any value;
};
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
        Condition condition = {
            .column = *column, .comparator = comparator, .value = value};
        conditions_.push_back(condition);
    }
    std::vector<Condition> conditions() { return conditions_; }
};
}  // namespace bll
