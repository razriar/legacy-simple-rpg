#pragma once

#include <optional>

#include "accesstoken.h"
#include "signindata.h"
#include "signupdata.h"

namespace bll {
enum SignUpStatus {
    Ok = 0,
    UserExists,
};
enum struct SignInStatus {
    Ok = 0,
    UserNotFound,
};
struct SignInResult {
    std::optional<AccessToken> token = std::nullopt;
    SignInStatus status = SignInStatus::Ok;
};
class IUserService {
   public:
    virtual ~IUserService() = default;
    virtual SignUpStatus SignUpUser(const SignUpData&) = 0;
    virtual SignInResult SignInUser(const SignInData&) = 0;
};
}  // namespace bll
