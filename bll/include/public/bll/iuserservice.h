#pragma once

#include "signupdata.h"

namespace bll {
enum SignUpStatus {
    Ok = 0,
    UserExists,
};
class IUserService {
   public:
    virtual ~IUserService() = default;
    virtual SignUpStatus SignUpUser(const SignUpData&) = 0;
};
}  // namespace bll
