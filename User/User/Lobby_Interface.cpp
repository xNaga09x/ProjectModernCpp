#include "Lobby_Interface.h"

Lobby_Interface::Lobby_Interface(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	getPLayers();

	runTime->start(1000);
	connect(runTime, SIGNAL(timeout()), this, SLOT(verifyStarted()));
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
	std::string start1 = "true";
	auto response3 = cpr::Put(cpr::Url{ "http://localhost:18080/startGame" }, cpr::Parameters{ { "start", start1} });

	cpr::Response response7 = cpr::Get(cpr::Url{ "http://localhost:18080/getUserType" });
	auto interfaceTypes = crow::json::load(response7.text);

	if (interfaceTypes) {
		// Preia?i valoarea boolean? pentru utilizatorul curent
		std::string userIsDrawer = "false";  // Seteaz? la true dac? utilizatorul curent este desenatorul

		for (const auto& interfaceType : interfaceTypes)
		{
			std::string playerName = interfaceType["name"].s();
			std::string boolValue = interfaceType["guesser"].s();
			qDebug() << playerName << " " << boolValue;

			if (playerName == this->getName()) {
				userIsDrawer = boolValue;
				break;
			}
		}

		if (userIsDrawer == "true") {
			Drawer_Game_Interface* draw = new Drawer_Game_Interface(this);
			draw->setName(this->getName());
			//this->close();
			this->hide();
			draw->show();
		}
		else if (userIsDrawer == "false") {
			Guess_Game_Interface* guesser = new Guess_Game_Interface(this);
			guesser->setName(this->getName());
			//this->close();
			this->hide();
			guesser->show();
		}
		else if (userIsDrawer == "end")
		{
			delete this;
		}

		QTimer* runTimer = new QTimer(this);
		connect(runTimer, SIGNAL(timeout()), this, SLOT(UserType()));
		runTimer->start(60000);
	}
}

void Lobby_Interface::verifyStarted()
{
	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/checkStarted" });
	auto check = crow::json::load(response.text);
	for (const auto& checked : check)
	{
		if (checked["start"].s() == "true" && ok == 0)
		{
			ok = 1;
			openInterface();
		}
	}
}

void Lobby_Interface::on_start_game_clicked()
{
	std::string start1 = "true";
	auto response = cpr::Put(cpr::Url{ "http://localhost:18080/startGame" }, cpr::Parameters{ { "start", start1} });
	openInterface();
	runTime->stop(); 
}
