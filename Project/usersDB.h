#pragma once
/*module*/
import game;
#include <string>
#include <vector>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;


//struct UserD
//{
//    int id;
//    std::string name;
//    float average;
//};
namespace gartic
{
    std::vector<User>temp=;
    inline auto createStorage(const std::string& filename)
    {

        return sql::make_storage(
            filename,
            sql::make_table(
                "Users",
                sql::make_column("id", &User::getId() ),
                sql::make_column("name", &User::getName()),
                sql::make_column("average", &User::getHistoryAverage())
            )
        );
    }
}


using Storage = decltype(createStorage(""));

void populateStorage(Storage& storage);
class AddToUser {
public:
	AddToUser(Storage& storage);

	crow::response operator() (const crow::request& req) const;

private:
	Storage& m_db;
};
