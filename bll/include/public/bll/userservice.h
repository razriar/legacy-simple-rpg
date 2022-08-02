#pragma once

#include <iostream>
#include <string>

#include "iuserservice.h"
#include "queries/creationquery.h"
#include "queries/existancequery.h"
#include "user.h"

namespace bll {
template <class DBContext>
class UserService : public IUserService {
   public:
    RegistrationStatus RegisterUser(const RegData &data) override {
        auto context = DBContext();
        {
            auto query = ExistanceQuery<User>();
            query.Require<User::Email>(Comparator::Equal, data.email);
            auto exists = context.Execute(query);
            std::cout << exists << std::endl;
            if (exists) return UserExists;
        }
        auto query = CreationQuery<User>();
        query.Add<User::Email>(data.email);
        query.Add<User::Password>(data.password);
        query.Add<User::Name>(data.name);
        query.Add<User::Nick>(data.nick);
        context.Execute(query);
        return Ok;
    }
};
}  // namespace bll
