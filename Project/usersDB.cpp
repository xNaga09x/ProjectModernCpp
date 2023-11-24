#include "usersDB.h"
void populateStorage(Storage& storage)
{
	std::vector<gartic::User> users{
	   gartic::User{ 1, "Pavel" },
	   gartic::User{ 2, "Petru" }, 
	   gartic::User{ 3, "Sergiu" },
	   gartic::User{ 4, "Iulian" }
	};
	storage.sync_schema();
	storage.insert_range(users.begin(), users.end());
}

AddToUser::AddToUser(Storage& storage)
	:m_db{ storage }
{

}

//crow::response AddToUser::operator()(const crow::request& req) const
//{
//	//extragerea datelor din cerere
//	auto json = crow::json::load(req.body);
//	if (!json)
//	{
//		return crow::response(400, "Invalid JSON in the request body");
//	}
//	//validarea si extragerea datelor utilizatorului
//	gartic::User newUser;
//	newUser.setId(json["id"].s());
//	newUser.setName(json["name"].s());
//	newUser.setHistoryAverage(json["average"].d());
//
//	auto newUserId = m_db.insert(newUser);
//
//	return crow::response(201, "User added with ID: " + std::to_string(newUserId));
//}
