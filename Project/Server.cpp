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
#include <algorithm>
#include <crow/websocket.h>
#include <sstream>
#include <cpr/cpr.h>

//void sendInfoToClients(bool boolValue, const std::string& stringValue) {
//	for (auto& conn : activeConnections) {
//		crow::json::wvalue message;
//		message["boolValue"] = boolValue;
//		message["stringValue"] = stringValue;
//		conn.send_text(crow::json::dump(message));
//	}
//}
using namespace gartic;

void run(const std::vector<crow::json::wvalue>& gameVerify, const std::vector<crow::json::wvalue>& active, Game& gameInstance)
{
	//alegem cuvant si drawer.
	if (gameVerify.size() > 0)
	{
		/*std::vector<User> players;
		for (auto l : active)
		{
			for (const auto& user : db.iterate<User>())
			{
				if ((crow::json::wvalue{ {"name", user.GetName()} } == l))
					players.push_back(user);
			}
		}*/


		auto usersResponse = cpr::Get(cpr::Url{ "http://localhost:18080/getUsers" });
		auto activeUsers = crow::json::load(usersResponse.text);
		std::cout << usersResponse.text;

		auto usersResponse1 = cpr::Get(cpr::Url{ "http://localhost:18080/users" });
		auto Users = crow::json::load(usersResponse1.text);
		std::cout << usersResponse1.text;

		std::vector<User> actives;

		for (auto userAct : activeUsers)
		{
			for (auto user : Users)
			{
				if (userAct["name"].s() == user["name"].s())

					actives.push_back(User(user["id"].i(), userAct["name"].s()));
			}
		}
		gameInstance.SetPlayers(actives);
		for (auto x : gameInstance.GetPlayers())
			std::cout << x.GetName() << " ";

		//Send word to server->client.
		gameInstance.FileRead();
		//std::string word = gameInstance.selectRandomWord(gameInstance.GetWords());




		bool userType;
		for (int i = 0; i < 4; i++)
		{
			//int noDraw = 0;
			for (auto x : actives)
			{
				gameInstance.SetDrawer(x);


				std::string word = gameInstance.selectRandomWord(gameInstance.GetWords());

				cpr::Parameters parameters = {
					{"word", word}, };

				auto response = cpr::Put(cpr::Url{ "http://localhost:18080/randomWord" }, parameters);
				std::cout << response.text;
				if (response.status_code == 200)
					std::cout << "Cuvântul a fost trimis cu succes la server!\n";
				else std::cerr << "Eroare la trimiterea cuvântului la server.\n";

				for (auto y : actives)
				{

					if (y.GetName() == gameInstance.GetDrawer().GetName())
					{
						cpr::Parameters parameters = {
								{"name", y.GetName()},
								{"guesser","true"}, };

						auto response = cpr::Put(cpr::Url{ "http://localhost:18080/UserType" }, parameters);

					}
					if (y.GetName() != gameInstance.GetDrawer().GetName())
					{
						cpr::Parameters parameters = {
								{"name", y.GetName()},
								{"guesser","false"}, };
						auto response = cpr::Put(cpr::Url{ "http://localhost:18080/UserType" }, parameters);
					}

				}
			}





			//		//start timer

			//	}
			//}
		}
	}
}


int main()
{
	/*-----------------------------------------Instantiation-----------------------------------------------*/

	//using namespace gartic;
	const std::string db_file = "products.sqlite";
	Storage db = createStorage(db_file);
	std::vector<crow::json::wvalue> chatMessages;
	std::vector<crow::json::wvalue> gameVerify;
	std::vector<crow::json::wvalue> active;
	std::vector<crow::json::wvalue> interfaces;
	std::vector<crow::json::wvalue> userType;
	crow::json::wvalue randomWord;
	std::vector<std::pair<std::string, bool>> nameBoolPairs; // Vector pentru a stoca perechi de nume și valori bool



	crow::SimpleApp app;
	Game gameInstance;
	db.sync_schema();

	auto initUsersCount = db.count<User>();
	if (initUsersCount == 0)
		populateStorage(db);

	auto usersCount = db.count<User>();

	/*-----------------------------------------ROUTING-----------------------------------------------*/

	CROW_ROUTE(app, "/")([]() {
		return "<html>"
			"<body>"
			"<p>This is the main lobby</p>"
			"<p>Go to the Game section: <a href=\"/game\">Game</a></p>"
			"<p>Go to the Users section: <a href=\"/users\">users</a></p>"
			"<p>Go to the chat section: <a href=\"/chat\">chat</a></p>"
			"<p>Go to the Drawer's section: <a href=\"/drawer\">WordToDraw</a></p>"
			"<p>Go to the Guesser's section: <a href=\"/guesser\">WordToGuess</a></p>"
			"</body>"
			"</html>";
		});

	CROW_ROUTE(app, "/game")([]() {
		return "This is the Game section";
		});

	CROW_ROUTE(app, "/startGame").methods(crow::HTTPMethod::Put)([&gameVerify, &active, &gameInstance](const crow::request& req) {

		std::string start{ req.url_params.get("start") };

		gameVerify.push_back(crow::json::wvalue{ { "start",start } });
		run(gameVerify, active, gameInstance);
		return crow::response(200);
		});

	CROW_ROUTE(app, "/randomWord").methods(crow::HTTPMethod::Put)([&randomWord](const crow::request& req) {

		std::string word{ req.url_params.get("word") };

		randomWord = crow::json::wvalue{ {"word",word} };

		return crow::response(200);
		});


	CROW_ROUTE(app, "/activeUsers").methods(crow::HTTPMethod::Put)([&active](const crow::request& req) {

		std::string name{ req.url_params.get("name") };

		active.push_back(crow::json::wvalue{
			{"name", name}
			});


		return crow::response(200);
		});

	CROW_ROUTE(app, "/verifyMethod").methods("GET"_method)([&gameVerify, &active, &gameInstance]() {

		run(gameVerify, active, gameInstance);
		return crow::response(200);
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
		std::string message{ req.url_params.get("Message") };
		std::string name{ req.url_params.get("Username") };

		// Store the message in the chatMessages deque
		chatMessages.push_back(crow::json::wvalue{
			{"Message",message},
			{"Username",name}
			});
		return crow::response(200);
		});

	CROW_ROUTE(app, "/get_chat").methods("GET"_method)([&chatMessages]() {
		std::vector<crow::json::wvalue> jsonMessages;
		for (auto x : chatMessages)
		{
			jsonMessages.push_back(crow::json::wvalue{ {x} });
		}
		return crow::json::wvalue{ jsonMessages };
		});

	CROW_ROUTE(app, "/getUsers").methods("GET"_method)([&active]() {
		std::vector<crow::json::wvalue> jsonMessages;
		for (auto x : active)
		{
			jsonMessages.push_back(crow::json::wvalue{ {x} });
		}
		return crow::json::wvalue{ jsonMessages };
		});

	CROW_ROUTE(app, "/get_random_word").methods("GET"_method)([&randomWord]()
		{
			return randomWord;
		});


	CROW_ROUTE(app, "/UserType").methods(crow::HTTPMethod::Put)([&userType](const crow::request& req) {
		// Extract the message from the request body
		std::string name{ req.url_params.get("name") };
		std::string type{ req.url_params.get("guesser") };

		// Store the message in the chatMessages deque
		userType.push_back(crow::json::wvalue{
			{"name",name},
			{"guesser",type}
			});
		return crow::response(200);
		});

	CROW_ROUTE(app, "/getUserType").methods("GET"_method)([&userType]() {
		std::vector<crow::json::wvalue> jsonTypes;
		for (auto x : userType)
		{
			jsonTypes.push_back(crow::json::wvalue{ {x} });
		}
		return crow::json::wvalue{ jsonTypes };
		});
	app.port(18080).multithreaded().run();

	//run(gameVerify, active, gameInstance);

	return 0;
}
//CROW_ROUTE(app, "/send_info")
//{
//	crow::json::rvalue jsonMessage = crow::json::load(data);
//			if (jsonMessage.has("boolValue") && jsonMessage["boolValue"].t() == crow::json::type::BOOL &&
//				jsonMessage.has("stringValue") && jsonMessage["stringValue"].t() == crow::json::type::STRING) {
//				bool boolValue = jsonMessage["boolValue"].b();
//				std::string stringValue = jsonMessage["stringValue"].s();
//				// Poți face ceva cu boolValue și stringValue aici
//				// Apoi, trimite informațiile către toate conexiunile WebSocket active
//				sendInfoToClients(boolValue, stringValue);
//			}
//});

//CROW_ROUTE(app, "/get_interface_type").methods("GET"_method)([&nameBoolPairs, &activeConnections](const crow::request& req) {
//	auto pairIter = nameBoolPairs.begin(); // Iterator pentru vectorul de perechi nume-bool
//	std::vector<crow::json::wvalue> interfaceTypes;
//	for (auto& conn : activeConnections) {
//		// Aici poți crea un obiect JSON pentru fiecare pereche nume-bool
//		crow::json::wvalue message;
//		message["name"] = pairIter->first;
//		message["boolValue"] = pairIter->second;
//		interfaceTypes.push_back(message);
//		++pairIter; // Mergi la următoarea pereche din vector
//	}
//	return crow::json::wvalue{ interfaceTypes };
//	});

//CROW_ROUTE(app, "/upload").methods("POST"_method)([](const crow::request& req)
//		{
//			// Decodifică imaginea Base64 primită în corpul cererii HTTP
//			std::string base64Image = req.body;
//			// Decodează Base64 și obține imaginea
//			QImage receivedImage;
//			receivedImage.loadFromData(QByteArray::fromBase64(QByteArray::fromStdString(base64Image)));
//			// Aici poți face ce dorești cu imaginea pe server (salvare într-un fișier, trimitere mai departe, etc.)
//			return crow::response("Image received successfully");
//		});
//CROW_ROUTE(app, "/get_chat").methods("GET"_method)([&chatMessages]() {
//	std::vector<crow::json::wvalue> jsonMessages;
//	// Iterați prin chatMessages și adăugați fiecare mesaj sub forma unui obiect JSON în vector
//	for (const auto& chatMessage : chatMessages) {
//		jsonMessages.push_back(crow::json::wvalue{
//			{"Message", chatMessage["Message"]},
//			{"Username", chatMessage["Username"]}
//			});
//	}
//	return crow::json::wvalue{
//		{"messages", jsonMessages}
//	};
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

//CROW_ROUTE(app, "/draw").methods(crow::HTTPMethod::Put)([&Drawing](const crow::request& req) {
//	// Extract the message from the request body
//	std::array<int> draw{ req.url_params.get() };
//	gartic::Draw newDraw;
//	newDraw.SetDraw(draw);
//	return crow::response(200);
//	});