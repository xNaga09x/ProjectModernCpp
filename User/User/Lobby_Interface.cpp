#include "Lobby_Interface.h"

Lobby_Interface::Lobby_Interface(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	guesser = nullptr;
	draw = nullptr;
	getPLayers();


}

Lobby_Interface::~Lobby_Interface()
{}

void Lobby_Interface::setName(std::string name)
{
	this->name = name;
}

std::string Lobby_Interface::getName()
{
	return this->name;
}

void Lobby_Interface::on_drawButton_clicked()
{
	this->close();
	draw = new Drawer_Game_Interface(this);
	draw->show();
}

void Lobby_Interface::getPLayers()
{

	QStandardItemModel* model = new QStandardItemModel();
	QStandardItem* item1 = new QStandardItem("Player 1");

	std::ofstream f("Text.txt");
	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/users" });
	std::cout << "Users:\n";
	auto users = crow::json::load(response.text);
	for (const auto& user : users)
	{
		QStandardItem* item1 = new QStandardItem(QString::fromStdString(user["name"].s()));

		model->appendRow(item1);

	}
	
	ui.playerList->setModel(model);
	

}
void Lobby_Interface::openInterface(bool type)
{
	if (type)
	{
		draw = new Drawer_Game_Interface(this);
		this->close();
		draw->show();
	}
	else
	{
		guesser = new Guess_Game_Interface(this);
		guesser->setName(this->getName());
		this->close();
		guesser->show();

	}
}
void Lobby_Interface::on_start_game_clicked()
{
	std::string start1 = "true";
	auto response = cpr::Put(cpr::Url{ "http://localhost:18080/startGame" }, cpr::Parameters{ { "start", start1} });
	/*guesser = new Guess_Game_Interface(this);
	this->close();
	guesser->show();*/
	
}
