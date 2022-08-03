#pragma once

#include <iostream>
#include <random>
#include <string>

#include "iuserservice.h"
#include "queries/creationquery.h"
#include "queries/existancequery.h"
#include "user.h"

namespace bll {
template <class DBContext>
class UserService : public IUserService {
   private:
    static std::string RandomString(std::size_t length) {
        static const std::string CHARS = "1234567890";
        std::random_device random_device;
        std::mt19937 generator(random_device());
        std::uniform_int_distribution<> distribution(0, CHARS.size() - 1);
        std::string random_string;
        for (std::size_t i = 0; i < length; ++i)
            random_string += CHARS[distribution(generator)];
        return random_string;
    }

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
        std::size_t secret_size = 10;
        query.Add<User::Secret>(RandomString(secret_size));
        context.Execute(query);
        return Ok;
    }
};
}  // namespace bll
