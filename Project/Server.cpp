#include <ctime>
#define EXCLUDE_WINDOWS_TIME_H
#include <sys/stat.h>
#define EXCLUDE_WINDOWS_STAT_H
#include "user.h"
import game;
import<iostream>;
import<vector>;
#include "StopWatch.h"
#include<filesystem>
#include<memory>
#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;
#include "usersDB.h"

int main()
{
	using namespace gartic;

	const std::string db_file = "usersDB.sqlite";
	Storage db = createStorage(db_file);
	db.sync_schema();
	//auto initialUsersCount = db.count<User>();
	/*if (initialUsersCount == 0)
		populateStorage(db);*/

		std::cout << "Introduceti Username-ul:";
		std::string name;
		std::cin >> name;

		std::vector<std::pair<uint32_t, int>> vect;
		vect.push_back(std::make_pair(1, 200));
		vect.push_back(std::make_pair(2, 400));
		vect.push_back(std::make_pair(3, 250));
		vect.push_back(std::make_pair(4, 500));

		User a = User(1, name, vect, 0);
		Game b = Game();
			b.FileRead();
			b.verifyGuessed(a);
			std::string word = b.getGuessedWord();
	crow::SimpleApp app;

	CROW_ROUTE(app, "/")([]() {
		return "This is an example app of crow and sql-orm";
		});


	/*CROW_ROUTE(app, "/Guesser")([word,a]() {
		std::vector<crow::json::wvalue> word_json;
		word_json.push_back(crow::json::wvalue{
			{"Name",a.getName()},
			{"Guess:", word}
			});
		return crow::json::wvalue{ word_json };
		});

	CROW_ROUTE(app, "/users")([&db]()
		{
			std::vector<crow::json::wvalue> users_json;
			for (const auto& user : db.iterate<User>())
			{
				users_json.push_back(crow::json::wvalue{
				{"id", user.getId()},
				{"name", user.getName()},
				{"average", user.getHistoryAverage()}
				});
			}
			return crow::json::wvalue{ users_json };
		});*/

	//CROW_ROUTE(app, "/add_user")
	//	.methods("POST"_method)([&db](const crow::request& req)
	//		{
	//			auto json = crow::json::load(req.body);
	//			if (!json)
	//			{
	//				return crow::response(400, "Bad Request: Invalid JSON format");
	//			}

	//			// validarea si extragerea datelor utilizatorului
	//			std::string name;
	//			float average;
	//			try
	//			{
	//				name = json["name"].s();
	//				average = json["average"].d();
	//			}
	//			catch (const std::exception& e)
	//			{
	//				return crow::response(400, "Bad Request: Missing or invalid fields in JSON");
	//			}

	//			// adaugarea userului in BD
	//			User newUser;
	//			newUser.setName(name);
	//			newUser.setHistoryAverage( average);
	//			db.addUser(newUser);

	//			return crow::response(201);
	//		});
	app.port(18080).multithreaded().run();
	return 0;
}