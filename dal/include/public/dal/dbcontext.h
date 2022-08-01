#pragma once

#include <iostream>
#include <map>
#include <pqxx/pqxx>
#include <string>

#include "bll/queries/creationquery.h"
#include "bll/queries/existancequery.h"
#include "convertor.h"

namespace dal {
class DBContext {
   private:
    std::map<bll::Comparator, std::string> comparators_;

   public:
    DBContext();
    template <class Object>
    void Execute(bll::CreationQuery<Object> query);
    template <class Object>
    bool Execute(bll::ExistanceQuery<Object> query);
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
    if (row[0].as<int>() == 0)
        return false;
    return true;
}
}  // namespace dal
