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
            sql::make_column("id", &gartic::User::getId, &gartic::User::setId, sql::primary_key().autoincrement()),
            sql::make_column("name", &gartic::User::getName, &gartic::User::setName)
        )
    );
}
using Storage = decltype(createStorage(""));
void populateStorage(Storage& storage);

class AddToUser {
public:
	AddToUser(Storage& storage);

	//crow::response operator() (const crow::request& req) const;

private:
	Storage& m_db;
};
