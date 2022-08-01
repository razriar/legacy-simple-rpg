#pragma once

#include <any>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <typeindex>

namespace dal {
class Convertor {
   private:
    std::map<std::type_index, std::function<std::string(std::any)>> convertors_;

   public:
    Convertor();
    std::string operator()(std::any);
};
}  // namespace dal
