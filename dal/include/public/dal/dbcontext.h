#pragma once

#include <iostream>
#include <map>
#include <pqxx/pqxx>
#include <string>

#include "bll/queries/creationquery.h"
#include "bll/queries/existancequery.h"
#include "bll/queries/selectionquery.h"
#include "convertor.h"

#include "bll/user.h"

namespace pqxx {
template <>
struct string_traits<bll::User::Id> : string_traits<bll::User::Id::ValueType> {
};
template <>
struct string_traits<bll::User::Email>
    : string_traits<bll::User::Email::ValueType> {};
template <>
struct string_traits<bll::User::Password>
    : string_traits<bll::User::Password::ValueType> {};
template <>
struct string_traits<bll::User::Name>
    : string_traits<bll::User::Name::ValueType> {};
template <>
struct string_traits<bll::User::Nick>
    : string_traits<bll::User::Nick::ValueType> {};
template <>
struct string_traits<bll::User::Secret>
    : string_traits<bll::User::Secret::ValueType> {};
template <>
struct nullness<bll::User::Id> : nullness<bll::User::Id::ValueType> {};
template <>
struct nullness<bll::User::Email> : nullness<bll::User::Email::ValueType> {};
template <>
struct nullness<bll::User::Password>
    : nullness<bll::User::Password::ValueType> {};
template <>
struct nullness<bll::User::Name> : nullness<bll::User::Name::ValueType> {};
template <>
struct nullness<bll::User::Nick> : nullness<bll::User::Nick::ValueType> {};
template <>
struct nullness<bll::User::Secret> : pqxx::no_null<bll::User::Secret> {};
//    : nullness<bll::User::Secret::ValueType> {};
}  // namespace pqxx

namespace dal {
template <typename IndexTuple, typename... T>
struct RowDataExtractorBase;
template <typename... T>
struct TupleDataExtractor
    : RowDataExtractorBase<std::index_sequence_for<T...>, T...> {};
template <std::size_t... Indexes, typename... T>
struct RowDataExtractorBase<std::index_sequence<Indexes...>, T...> {
    static void Assign(std::tuple<T&...> consumer,
                       std::tuple<T...>& supplier) {
        ((std::get<Indexes>(supplier) = std::get<Indexes>(consumer)), ...);
    }
};
class DBContext {
   private:
    std::map<bll::Comparator, std::string> comparators_;

   public:
    DBContext();
    template <class Object>
    void Execute(bll::CreationQuery<Object> query);
    template <class Object>
    bool Execute(bll::ExistanceQuery<Object> query);
    template <class Object>
    Object Execute(bll::SelectionQuery<Object> query);
};
template <class Object>
void DBContext::Execute(bll::CreationQuery<Object> query) {
    auto querystr = std::string();
    querystr += "INSERT INTO " + query.table();
    auto columns = std::string();
    auto values = std::string();
    auto convertor = Convertor();
    for (const auto& column : query.columns()) {
        columns += column.name + ", ";
        values += convertor(column.value) + ", ";
    }
    columns.erase(columns.size() - 2);
    values.erase(values.size() - 2);
    columns = " (" + columns + ")";
    values = " VALUES (" + values + ");";
    querystr += columns + values;
    std::cout << querystr << std::endl;
    pqxx::connection c("postgres://postgres:1234@localhost:5432");
    pqxx::work w(c);
    w.exec0(querystr);
    w.commit();
}
template <class Object>
bool DBContext::Execute(bll::ExistanceQuery<Object> query) {
    auto querystr = std::string();
    querystr += "SELECT COUNT(*) FROM " + query.table();
    auto convertor = Convertor();
    if (query.conditions().size()) querystr += " WHERE ";
    auto conditions = std::string();
    for (const auto& condition : query.conditions()) {
        auto column = condition.column;
        std::string comparator = comparators_[condition.comparator];
        std::string value = convertor(condition.value);
        conditions += column + " " + comparator + " " + value + " AND ";
    }
    conditions.erase(conditions.size() - 5);
    querystr += conditions + ";";
    std::cout << querystr << std::endl;
    pqxx::connection c("postgres://postgres:1234@localhost:5432");
    pqxx::work w(c);
    auto row = w.exec1(querystr);
    if (row[0].as<int>() == 0) return false;
    return true;
}
template <class Object>
Object DBContext::Execute(bll::SelectionQuery<Object> query) {
    auto querystr = std::string();
    querystr += "SELECT * FROM " + query.table();
    auto convertor = Convertor();
    if (query.conditions().size()) querystr += " WHERE ";
    auto conditions = std::string();
    for (const auto& condition : query.conditions()) {
        auto column = condition.column;
        std::string comparator = comparators_[condition.comparator];
        std::string value = convertor(condition.value);
        conditions += column + " " + comparator + " " + value + " AND ";
    }
    conditions.erase(conditions.size() - 5);
    querystr += conditions + ";";
    std::cout << querystr << std::endl;
    pqxx::connection c("postgres://postgres:1234@localhost:5432");
    pqxx::work w(c);
    auto row = w.exec1(querystr);
    Object object;
    auto tuple = object.Introspect();
    row.to(tuple);
    return object;
}
}  // namespace dal
