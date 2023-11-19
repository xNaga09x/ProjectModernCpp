#pragma once

//module user;
#include <string>
#include <vector>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;


import user;
inline auto createStorage(const std::string& filename)
{
    return sql::make_storage(
        filename,
        sql::make_table(
            "User",
            sql::make_column("id", &gartic::User::getId, &gartic::User::setId),
           sql::make_column("name", &gartic::User::getName, &gartic::User::setName),
            sql::make_column("average", &gartic::User::getHistoryAverage, &gartic::User::setHistoryAverage, sql::primary_key())
        )
    );
}
using Storage = decltype(createStorage(""));
//void populateStorage(Storage& storage);
//class AddToUser {
//public:
//	AddToUser(Storage& storage);
//
//	crow::response operator() (const crow::request& req) const;
//
//private:
//	Storage& m_db;
//};
