#pragma once

#include <string>

namespace bll {
struct AccessToken {
    int id;
    std::string secret;
    auto Introspect() {
        return std::tie(id, secret);
    }
};
}  // namespace bll
