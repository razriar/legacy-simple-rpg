#pragma once

#include <boost/beast/http.hpp>
#include <string>

namespace dtl {
enum ResponseStatus {
    Ok = 200,
    Created = 201,
    NotFound = 404,
    Conflict = 409,
    BadRequest = 400
};
class Response {
   private:
    std::string body_;
    ResponseStatus code_;

   public:
    Response() {
        body_ = "Target not found";
        code_ = ResponseStatus::NotFound;
    }
    std::string body() { return body_; }
    std::string set_body(const std::string &other_body) {
        body_ = other_body;
        return body_;
    }
    ResponseStatus code() { return code_; }
    ResponseStatus set_code(ResponseStatus code) {
        code_ = code;
        return code_;
    }
    operator boost::beast::http::response<boost::beast::http::string_body>() {
        namespace http = boost::beast::http;
        auto response = http::response<http::string_body>();
        response.body() = body_;
        response.result(code_);
        return response;
    }
};
}  // namespace dtl
