#pragma once

#include <bll/signupdata.h>
#include <bll/registry.h>

#include <iostream>
#include <nlohmann/json.hpp>

#include "dtl/request.h"
#include "dtl/response.h"
#include "dtl/target.h"

namespace dtl {
class SignUpAction {
   public:
    static Target RequestTarget() { return std::string("/api/register"); }
    static Response Put(const Request& request) {
        using json = nlohmann::json;
        auto data = json::parse(request.body());
        auto reg_data = bll::SignUpData();
        try {
            reg_data.email = data["email"];
            reg_data.password = data["password"];
            reg_data.name = data["name"];
            reg_data.nick = data["nick"];
        } catch (json::type_error& e) {
            std::cerr << e.what() << std::endl;
            auto response = Response();
            response.set_body("Missing required data");
            response.set_code(ResponseStatus::BadRequest);
            return response;
        }
        auto service = bll::Registry::GetUserService();
        auto status = service->SignUpUser(reg_data);
        auto response = Response();
        json body;
        ResponseStatus code;
        if (status == bll::SignUpStatus::UserExists) {
            body["error"] = "User with that email already exists";
            code = ResponseStatus::Conflict;
        } else if (status == bll::SignUpStatus::Ok) {
            body["ok"] = "Ok";
            code = ResponseStatus::Created;
        }
        response.set_body(body.dump());
        response.set_code(code);
        return response;
    }
};
}  // namespace dtl
