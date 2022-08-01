#pragma once

#include <string>

#include "property.h"

namespace bll {
struct User {
    class Id : public Property<User, int> {};
    class Email : public Property<User, std::string> {};
    class Password : public Property<User, std::string> {};
    class FirstName : public Property<User, std::string> {};
    class LastName : public Property<User, std::string> {};
    class Nick : public Property<User, std::string> {};

    Id id;
    Email email;
    Password password;
    FirstName first_name;
    LastName last_name;
    Nick nick;
};
}  // namespace bll
