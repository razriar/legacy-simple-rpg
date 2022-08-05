#pragma once

#include <optional>
#include <string>

namespace bll {
template <class Owned, class Owner>
concept OwnedBy = requires() {
    typename Owned::OwnerType;
    std::is_same<typename Owned::OwnerType, Owner>::value;
};
template <class Owner, class Value>
class Property {
    Value value_;
public:
    using OwnerType = Owner;
    using ValueType = Value;

    Property() = default;
    Property(const Value& value) : value_(value) {}
    Property& operator=(const Value& value) {
        value_ = value;
    };
    operator Value() {
        return value_;
    }
};
} // namespace bll
