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
#include "usersDB.h"

int main()
{
	using namespace gartic;
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

	CROW_ROUTE(app, "/")([]() {
		return "This is a test.";
		});

	CROW_ROUTE(app, "/game")([]() {
		return "This will be the game URL.";
		});

	CROW_ROUTE(app, "/guesser")([word,a]() {
		std::vector<crow::json::wvalue> word_json;
		word_json.push_back(crow::json::wvalue{
			{"Name",a.getName()},
			{"Guess:", word}
			});
		//return "This is path.";
		return crow::json::wvalue{ word_json };
		});

	/*CROW_ROUTE(app, "/users")([&db]() {
		return "This will be the users database.";
		});*/

	app.port(18080).multithreaded().run();
	return 0;
}