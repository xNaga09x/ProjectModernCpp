#include <iostream>
#include <numeric>
#include <sstream>
#include <regex>
#include <string>
#include <cpr/cpr.h>
#include <crow.h>

int main()
{
	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080" });

	std::cout << "Here is the content of the URL:\n";
    std::cout << response.text;

	return 0;
}