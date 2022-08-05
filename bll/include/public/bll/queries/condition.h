#pragma once

#include <any>
#include <string>

namespace bll {
enum Comparator {
    Equal = 0,
};
struct Condition {
    std::string column;
    Comparator comparator;
    std::any value;
};
}  // namespace bll
