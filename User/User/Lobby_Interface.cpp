#include "Lobby_Interface.h"

Lobby_Interface::Lobby_Interface(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	guesser = nullptr;
	getPLayers();
}

Lobby_Interface::~Lobby_Interface()
{}

void Lobby_Interface::getPLayers()
{
	std::ofstream f("Text.txt");
	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/users" });
	std::cout << "Users:\n";
	auto users = crow::json::load(response.text);
	for (const auto& user : users)
	{
		f <<user["name"] << std::endl;

	}



}

void Lobby_Interface::on_start_game_clicked()
{
	this->close();
	guesser = new Guess_Game_Interface(this);
	guesser->show();
}