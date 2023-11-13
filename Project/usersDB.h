module;
import user;
#pragma once
#include <string>
#include <vector>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

namespace gartic
{
    class User;
    inline auto createStorage(const std::string& filename)
    {
        gartic::User tempUser;
        auto idGetter = [&tempUser]() { return tempUser.getId(); };
        auto nameGetter = [&tempUser]() { return tempUser.getName(); };
        auto averageGetter = [&tempUser]() { return tempUser.getHistoryAverage(); };

        return sql::make_storage(
            filename,
            sql::make_table(
                "Users",
                sql::make_column("id", idGetter, sql::primary_key().autoincrement()),
                sql::make_column("name", nameGetter),
                sql::make_column("average", averageGetter)
            )
        );
    }
}

using Storage = decltype(createStorage(""));

void populateStorage(Storage& storage);
//class AddToUser {
//public:
//	AddToUser(Storage& storage);
//
//	crow::response operator() (const crow::request& req) const;
//
//private:
//	Storage& m_db;
//};
