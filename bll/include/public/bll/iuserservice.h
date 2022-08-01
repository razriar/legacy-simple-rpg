#pragma once

#include "regdata.h"

namespace bll {
enum RegistrationStatus {
    Ok = 0,
    UserExists,
};
class IUserService {
   public:
    virtual RegistrationStatus RegisterUser(const RegData&) = 0;
};
}  // namespace bll
