#pragma once

#include <string>
#include <tuple>

#include "property.h"

namespace bll {
struct User {
    class Id : public Property<User, int> {
       public:
        using Property<User, int>::Property;
    };
    class Email : public Property<User, std::string> {
       public:
        using Property<User, std::string>::Property;
    };
    class Password : public Property<User, std::string> {
       public:
        using Property<User, std::string>::Property;
    };
    class Name : public Property<User, std::string> {
       public:
        using Property<User, std::string>::Property;
    };
    class Nick : public Property<User, std::string> {
       public:
        using Property<User, std::string>::Property;
    };
    class Secret : public Property<User, std::string> {
       public:
        using Property<User, std::string>::Property;
    };

    Id id;
    Email email;
    Password password;
    Name name;
    Nick nick;
    Secret secret;

    auto Introspect() {
        return std::tie(id, email, password, name, nick, secret);
    }
};
}  // namespace bll
