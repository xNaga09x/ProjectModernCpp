#pragma once
module user;

#include <string>
#include <vector>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

inline auto createStorage(const std::string& filename)
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"Users",
			sql::make_column("id",&User::m_id),
			sql::make_column("name",&User::m_name),
			sql::make_column("average",&User::m_historyAverage)
			)

		);



}
using Storage = decltype(createStorage(""));

void populateStorage(Storage& storage);

class AddToUser {
public:
	AddToUser(Storage& storage);

	crow::response operator() (const crow::request& req) const;

private:
	Storage& m_dbUsers;
};
