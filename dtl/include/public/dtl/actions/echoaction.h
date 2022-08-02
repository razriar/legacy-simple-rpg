#pragma once

#include "dtl/request.h"
#include "dtl/response.h"
#include "dtl/target.h"

namespace dtl {
class EchoAction {
   public:
    static Target Target() { return std::string("/echo"); }
    static Response Get(const Request &request) {
        auto response = Response();
        response.set_body(request.body());
        response.set_code(ResponseStatus::Ok);
        return response;
    }
};
}  // namespace dtl
