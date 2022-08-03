#pragma once

#include <string>

namespace bll {
struct SignUpData {
    std::string email;
    std::string password;
    std::string name;
    std::string nick;
};
}  // namespace bll
