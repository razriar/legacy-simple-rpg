#pragma once

#include <bll/signindata.h>
#include <bll/registry.h>

#include <iostream>
#include <nlohmann/json.hpp>

#include "dtl/request.h"
#include "dtl/response.h"
#include "dtl/target.h"

namespace dtl {
class SignInAction {
   public:
    static Target RequestTarget() { return std::string("/api/signin"); }
    static Response Post(const Request &request) {
        using json = nlohmann::json;
        auto data = json::parse(request.body());
        auto signin_data = bll::SignInData();
        try {
            signin_data.email = data["email"];
            signin_data.password = data["password"];
        } catch (json::type_error& e) {
            std::cerr << e.what() << std::endl;
            auto response = Response();
            response.set_body("Missing required data");
            response.set_code(ResponseStatus::BadRequest);
            return response;
        }
        auto service = bll::Registry::GetUserService();
        auto result = service->SignInUser(signin_data);
        auto response = Response();
        json body;
        ResponseStatus code;
        if (result.status == bll::SignInStatus::UserNotFound) {
            body["error"] = "User not found";
            code = ResponseStatus::NotFound;
        } else if (result.status == bll::SignInStatus::Ok) {
            json token;
            token["id"] = result.token->id;
            token["secret"] = result.token->secret;
            body["token"] = token;
            code = ResponseStatus::Ok;
        }
        response.set_body(body.dump());
        response.set_code(code);
        return response;
        return Response();
    }
};
}  // namespace dtl
