#include "dal/convertor.h"

namespace dal {
Convertor::Convertor() {
    auto int_convertor = [](std::any any) {
        return std::to_string(std::any_cast<int>(any));
    };
    convertors_[std::type_index(typeid(int))] = int_convertor;
    auto string_convertor = [](std::any any) {
        auto value = std::any_cast<std::string>(any);
        return "'" + value + "'";
    };
    convertors_[std::type_index(typeid(std::string))] = string_convertor;
    auto const_char_ptr_convertor = [](std::any any) {
        auto value = std::any_cast<const char*>(any);
        return "'" + std::string(value) + "'";
    };
    convertors_[std::type_index(typeid(const char*))] =
        const_char_ptr_convertor;
}
std::string Convertor::operator()(std::any any) {
    std::string result;
    try {
        auto convertor = convertors_[std::type_index(any.type())];
        result = convertor(any);
    } catch (const std::out_of_range& e) {
        throw std::invalid_argument("No matching convertor found");
    }
    return result;
}
}  // namespace dal
