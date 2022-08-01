#pragma once

#include <optional>
#include <string>

namespace bll {
template <class T>
class Metadata {
private:
    inline static std::optional<std::string> TableName_;
    inline static std::optional<std::string> ColumnName_;
public:
    friend void InitMetadata();
    static std::optional<std::string> TableName() {
        return TableName_;
    }
    static std::optional<std::string> ColumnName() {
        return ColumnName_;
    }
};
void InitMetadata();
}  // namespace bll
