#include <iostream>
#include <numeric>
#include <sstream>
#include <regex>
#include <string>
#include <cpr/cpr.h>
#include <crow.h>

int main()
{
	

	
	std::string name;
	std::cout << "Introduceti Numele : ";
	std::cin >> name;
	
	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/users" });
	auto players = crow::json::load(response.text);
	
	for (const auto& player : players)
	{
		if (player["name"] != name)
			auto response = cpr::Put(
				cpr::Url{ "http://localhost:18080/adduser" },
				cpr::Payload{
					{ "name", name }
				}
		);
		
		if (response.status_code == 200)
			std::cout << "You added a name succesfully";
		break;
	}
}