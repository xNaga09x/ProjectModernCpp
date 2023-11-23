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

	const std::string db_file = "products.sqlite";
	Storage db = createStorage(db_file);
	db.sync_schema();

	auto initUsersCount = db.count<User>();
	if (initUsersCount == 0)
		populateStorage(db);

	auto usersCount = db.count<User>();
	std::cout << "\nusersCount = " << usersCount << '\n';

	crow::SimpleApp app;

	CROW_ROUTE(app, "/")([]() {
		//auto page = crow::mustache::load_text("fancypage.html");
		//return page;
		return "This is a test.";
		});

	CROW_ROUTE(app, "/game")([]() {
		return "This will be the game URL.";
		});

	CROW_ROUTE(app, "/guesser")([word, a]() {
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
			//std::string product_json = db.dump(user);			
		}
		return crow::json::wvalue{ users_json };
	});

	//Incercare addUser V1

	//std::string name = "NumeUtilizator";
	//float average = 3.5;

	//// Construiește JSON-ul
	//std::string json_data = R"({"name": ")" + name + R"(", "average": )" + std::to_string(average) + "}";

	//// Trimite cererea POST către server
	//cpr::Response r = cpr::Post(cpr::Url{ "http://localhost:18080/addUser" },
	//	cpr::Header{ {"Content-Type", "application/json"} },
	//	cpr::Body{ json_data });

	//// Verifică dacă cererea a fost realizată cu succes
	//if (r.status_code == 201) {
	//	std::cout << "User adăugat cu succes!\n";
	//}
	//else {
	//	std::cerr << "Eroare la adăugarea utilizatorului. Cod de stare: " << r.status_code << "\n";
	//}

	//CROW_ROUTE(app, "/addUser").methods("POST"_method)([&db](const crow::request& req) 
	//{
	//	// Parsare și procesare cerere POST
	//	auto json = crow::json::load(req.body);
	//	if (!json)
	//	{
	//		return crow::response(400, "Invalid JSON");
	//	}

	//	// Extrage informațiile despre utilizator din JSON
	//	//int id= json["id"].s();
	//	std::string name = json["name"].s();
	//	float average = json["average"].d();

	//	// Creează un obiect User și adaugă-l în baza de date
	//	gartic::User newUser(0, name, average); // Id-ul va fi setat automat de baza de date
	//	db.insert(newUser);

	//	return crow::response(201); // Răspuns pentru succes
	//	});

	//Incercare addUser V2
	//CROW_ROUTE(app, "/adduser/<int>")([&db](const crow::request& req, int userId) {
	//	gartic::User newUser;
	//	newUser.setId(userId);
	//	std::cout << "Introduceti nume:";
	//	std::String name;
	//	std::cin >> name;
	//	float average;
	//	std::cin >> avg;
	//	newUser.setName(name);
	//	newUser.setHistoryAverage(avg);
	//	db.insert(newUser);

	//	return crow::response(200);
	//	});

	//auto& addToUserPut = CROW_ROUTE(app, "/adduser").methods(crow::HTTPMethod::PUT); // https://stackoverflow.com/a/630475/12388382
	//addToUserPut(AddToUserHandler(db));

	app.port(18080).multithreaded().run();
	return 0;
}