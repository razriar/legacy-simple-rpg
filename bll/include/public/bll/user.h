#pragma once

#include <string>

#include "property.h"

namespace bll {
struct User {
    class Id : public Property<User, int> {};
    class Email : public Property<User, std::string> {};
    class Password : public Property<User, std::string> {};
    class Name : public Property<User, std::string> {};
    class Nick : public Property<User, std::string> {};
    class Secret : public Property<User, std::string> {};

    Email email;
    Password password;
    Name name;
    Nick nick;
    Secret secret;
};
}  // namespace bll
