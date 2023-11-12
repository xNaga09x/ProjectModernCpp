#include <ctime>
#define EXCLUDE_WINDOWS_TIME_H
#include <sys/stat.h>
#define EXCLUDE_WINDOWS_STAT_H
#include "StopWatch.h"
import user;
import game;
import<iostream>;
import<vector>;

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
	Storage Usersdb = createStorage(db_file);
	db.sync_schema();
	auto initialUsersCount = db.count<User>();


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
		b.verifyGuessed();
		std::string word = b.getGuessedWord();

	crow::SimpleApp app;
	CROW_ROUTE(app, "/Guesser")([word,&Usersdb]() {
		std::vector<crow::json::wvalue> word_json;
		word_json.push_back(crow::json::wvalue{
			{"Name",Usersdb.name()},
			{"Guess:", word}
			});
		return crow::json::wvalue{ word_json };
		});
	app.port(18080).multithreaded().run();
	return 0;
}