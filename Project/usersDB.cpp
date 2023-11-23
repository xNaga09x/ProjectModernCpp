#include "usersDB.h"
void populateStorage(Storage& storage)
{
	std::vector<gartic::User> users{
	   gartic::User{ 1, "Pavel", 5.f },
	   gartic::User{ 2, "Petru", 0.2f },  //Punem -1 pt ca atunci cand inseram nu stim cate elemente avem in BD
	   gartic::User{ 3, "Sergiu", 2.f },
	   gartic::User{ 4, "Iulian", 8.f }
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
