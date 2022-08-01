#pragma once

#include <memory>

#include "iuserservice.h"

namespace bll {
struct Registry {
   private:
    inline static std::shared_ptr<IUserService> user_service_ = nullptr;

   public:
    static std::shared_ptr<IUserService> GetUserService() {
        if (!user_service_) throw std::runtime_error("User service is not set");
        return user_service_;
    }
    static void SetUserService(std::shared_ptr<IUserService> service) {
        user_service_ = service;
    }
};
}  // namespace bll
