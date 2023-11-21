#include "usersDB.h"

//using gartic::User;
//
//void populateStorage(Storage& storage)
//{
//	std::vector<User> users;
//	std::vector<std::pair<uint32_t, int>>matchHistory;
//	std::pair<uint32_t, int> match1{ 31,1 };
//	std::pair<uint32_t, int> match2{ 32,2 };
//	std::pair<uint32_t, int> match3{ 31,3 };
//	std::pair<uint32_t, int> match4{ 31,4 };
//	std::pair<uint32_t, int> match5{ 31,5 };
//	matchHistory.push_back(match1);
//	matchHistory.push_back(match2);
//	matchHistory.push_back(match3);
//	matchHistory.push_back(match4);
//	matchHistory.push_back(match5);
//	User user1{ -1,"Andrei",matchHistory,31.3,false };
//	User user2{ -1,"Ion",matchHistory,31.2,false };
//	User user3{ -1,"Marin",matchHistory,31,false };
//	users.push_back(user1);
//	users.push_back(user2);
//	users.push_back(user3);
//	//storage.sync_schema();
//	storage.insert_range(users.begin(), users.end());
//}

//
//AddToUser::AddToUser(Storage& storage)
//	:m_db{ storage }
//{
//
//}
//
//crow::response AddToUser::operator()(const crow::request& req) const
//{
//	//extragerea datelor din cerere
//	auto json = crow::json::load(req.body);
//	if (!json)
//	{
//		return crow::response(400, "Invalid JSON in the request body");
//	}
//	//validarea si extragerea datelor utilizatorului
//	UserD newUser;
//	newUser.name = json["name"].s();
//	newUser.average = json["average"].d();
//
//	auto newUserId = m_db.insert(newUser);
//
//	return crow::response(201, "User added with ID: " + std::to_string(newUserId));
//
//
//}
