#include <ctime>
#define EXCLUDE_WINDOWS_TIME_H
#include <sys/stat.h>
#define EXCLUDE_WINDOWS_STAT_H
#include "StopWatch.h"
import user;
import game;
import<iostream>;
import<vector>;
#include<deque>
#include<filesystem>
#include<memory>
#include <crow.h>
#include "usersDB.h"

int main()
{
	using namespace gartic;
	//std::cout << "Introduceti Username-ul:";
	//std::string name;
	//std::cin >> name;
	//User a = User(1, name);
	//Game b = Game();
	//b.FileRead();
	//b.verifyGuessed();
	//std::string word = b.GetGuessedWord();


	const std::string db_file = "products.sqlite";
	Storage db = createStorage(db_file);
	db.sync_schema();

	auto initUsersCount = db.count<User>();
	if (initUsersCount == 0)
		populateStorage(db);

	auto usersCount = db.count<User>();
	std::cout << "\nusersCount = " << usersCount << '\n';

	std::deque<std::string> chatMessages;

	crow::SimpleApp app;


	CROW_ROUTE(app, "/")([]() {
		return "<html>"
			"<body>"
			"<p>This is the main lobby</p>"
			"<p>Go to the Game section: <a href=\"/game\">Game</a></p>"
			"<p>Go to the Users section: <a href=\"/users\">users</a></p>"
			"<p>Go to the chat section: <a href=\"/chat\">chat</a></p>"
			"<p>Go to the Guesser's section: <a href=\"/guesser\">WordToGuess</a></p>"
			"</body>"
			"</html>";
		});

	//CROW_ROUTE(app, "/draw").methods(crow::HTTPMethod::Put)([&Drawing](const crow::request& req) {

	//	// Extract the message from the request body
	//	std::array<int> draw{ req.url_params.get() };

	//	gartic::Draw newDraw;
	//	newDraw.SetDraw(draw);

	//	return crow::response(200);
	//	});

	//CROW_ROUTE(app, "/get_draw").methods("GET"_method)([&Drawing]() {
	//	std::array<crow::json::wvalue> jsonDraw;
	//	for (auto x : Drawing)
	//	{
	//		jsonDraw.push_back(crow::json::wvalue{
	//				x
	//			});
	//	}
	//	return crow::json::wvalue{ jsonDraw };
	//	});

	CROW_ROUTE(app, "/game")([]() {
		return "This is the Game section";
		});


	CROW_ROUTE(app, "/users")([&db]()
		{
			std::vector<crow::json::wvalue> users_json;

			for (const auto& user : db.iterate<User>())
			{
				users_json.push_back(crow::json::wvalue{
					{"id", user.GetId()},
					{"name", user.GetName()},
					});
			}
			return crow::json::wvalue{ users_json };
		});

	CROW_ROUTE(app, "/adduser").methods(crow::HTTPMethod::Put)([&db](const crow::request& req)
		{
			std::string name{ req.url_params.get("name") };

			gartic::User newUser;
			newUser.SetName(name);
			db.insert(newUser);

			return crow::response(200);
		});

	CROW_ROUTE(app, "/chat").methods(crow::HTTPMethod::Put)([&chatMessages](const crow::request& req) {
		

		// Extract the message from the request body
		std::string message{ req.url_params.get("You") };

		// Store the message in the chatMessages deque
		chatMessages.push_back(message);

		return crow::response(200);
		});

	CROW_ROUTE(app, "/get_chat").methods("GET"_method)([&chatMessages]() {
		std::vector<crow::json::wvalue> jsonMessages;
		std::string a;
		for (auto x : chatMessages)
		{
			jsonMessages.push_back(crow::json::wvalue{
					{"message", x},
				
				});
		}
		return crow::json::wvalue{ jsonMessages };
		});

	app.port(18080).multithreaded().run();
	return 0;
}