#pragma once

#include <concepts>
#include <functional>
#include <map>
#include <utility>

#include "method.h"
#include "request.h"
#include "response.h"
#include "target.h"

namespace dtl {
typedef std::function<Response(const Request&)> Handler;
template <class Action>
concept Targeted = requires() {
    { Action::Target() } -> std::same_as<Target>;
};
template <class Action>
concept GetResponding = requires(const Request& request) {
    { Action::Get(request) } -> std::same_as<Response>;
};
template <class Action>
concept PostResponding = requires(const Request& request) {
    { Action::Post(request) } -> std::same_as<Response>;
};
template <class T1, class T2>
concept ConstructibleTo = std::constructible_from<T2, T1>;
template <class T1, class T2>
concept ConvertibleFrom = std::convertible_to<T2, T1>;
class FrontController {
   private:
    std::map<std::string, Method> methods_;
    std::map<std::pair<Target, Method>, Handler> map_;
    Response default_response_;

   public:
    FrontController() {
        methods_["GET"] = Method::Get;
        methods_["POST"] = Method::Post;
    }

    template <Targeted Action>
    void RegisterAction() {
        auto target = Action::Target();
        if constexpr (GetResponding<Action>) {
            auto key = std::pair(target, Method::Get);
            map_[key] = &Action::Get;
        }
        if constexpr (PostResponding<Action>) {
            auto key = std::pair(target, Method::Post);
            map_[key] = &Action::Post;
        }
    }
    template <ConstructibleTo<Request> RawRequest,
              ConvertibleFrom<Response> RawResponse>
    RawResponse Handle(const RawRequest& raw_request) {
        auto request = Request(raw_request);
        auto target = request.target();
        auto method = request.method();
        std::cout << target << (method == Method::Get) << std::endl;
        auto key = std::pair(target, method);
        auto response = default_response_;
        if (map_.contains(key)) {
            auto handler = map_[key];
            response = handler(request);
        }
        return response;
    }
};
}  // namespace dtl
