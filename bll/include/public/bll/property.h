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
public:
    using OwnerType = Owner;
    using ValueType = Value;
};
} // namespace bll
