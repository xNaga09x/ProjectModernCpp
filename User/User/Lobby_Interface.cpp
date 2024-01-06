#include "Lobby_Interface.h"

Lobby_Interface::Lobby_Interface(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
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
void Lobby_Interface::openInterface()
{

	Transition* transition = new Transition(this);
	transition->setName(this->getName());
	transition->show();
	this->close();
	/*cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/getUserType" });
	auto interfaceTypes = crow::json::load(response.text);*/

	//if (interfaceTypes) {
	//	// Preia?i valoarea boolean? pentru utilizatorul curent
	//	std::string userIsDrawer = "false";  // Seteaz? la true dac? utilizatorul curent este desenatorul

	//	for (const auto& interfaceType : interfaceTypes) {
	//		std::string playerName = interfaceType["name"].s();
	//		std::string boolValue = interfaceType["guesser"].s();

	//		if (playerName == this->getName()) {
	//			userIsDrawer = boolValue;
	//			break;
	//		}
	//	}

	//	/*if (userIsDrawer=="true") {
	//		Drawer_Game_Interface* draw= new Drawer_Game_Interface(this);
	//		draw->setName(this->getName());
	//		this->close();
	//		draw->show();
	//	}
	//	else if (userIsDrawer == "false") {
	//		Guess_Game_Interface* guesser= new Guess_Game_Interface(this);
	//		guesser->setName(this->getName());
	//		this->close();
	//		guesser->show();
	//	}*/


	//}

}
void Lobby_Interface::on_start_game_clicked()
{
	std::string start1 = "true";
	auto response = cpr::Put(cpr::Url{ "http://localhost:18080/startGame" }, cpr::Parameters{ { "start", start1} });
	/* openInterface(); */

		Guess_Game_Interface * guesser = new Guess_Game_Interface(this);
	guesser->setName(this->getName());
	guesser->show();

	Drawer_Game_Interface* draw = new Drawer_Game_Interface(this);
	draw->setName(this->getName());
	draw->show();

	this->close();
	///*std::string start1 = "true";
	//auto response = cpr::Put(cpr::Url{ "http://localhost:18080/startGame" }, cpr::Parameters{ { "start", start1} });*/
	//openInterface();
	///*guesser = new Guess_Game_Interface(this);
	//guesser->setName(this->getName());
	//this->close();
	//guesser->show();*/
	
}
