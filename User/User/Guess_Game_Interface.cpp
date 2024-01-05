#include "Guess_Game_Interface.h"

Guess_Game_Interface::Guess_Game_Interface(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("Main Game");

	setWord();
	updateTimer = new QTimer(this); 
	getPLayers(); 
	// Connect signals and slots
	connect(updateTimer, SIGNAL(timeout()), this, SLOT(updatePlayerList()));
	connect(ui.sendButton, SIGNAL(clicked()), this, SLOT(sendMessage())); 

	updateTimer->start(10000);

	QTimer* chatUpdateTimer = new QTimer(this); 
	connect(chatUpdateTimer, SIGNAL(timeout()), this, SLOT(updateChat())); 
	chatUpdateTimer->start(3000);

	for (int i = 0; i < word.size(); i++)
	{
		if(i< word.size()-1)
		secretword += "_ ";
		else
			secretword += "_";
	}
	const QString qword = QString::fromStdString(secretword);

	ui.GuessWord->setText(qword);
	ui.GuessWord->setAlignment(Qt::AlignCenter);

	ui.GuessWord->show();
	
	QTimer* runTimer = new QTimer(this);
	connect(runTimer, SIGNAL(timeout()), this, SLOT(closeWindow()));
	runTimer->start(4000);
}
void Guess_Game_Interface::closeWindow()
{
	/*Transition* lobby = new Transition(this);
	lobby->setName(this->getName());
	lobby->show();
	this->close();*/
	delete this;

	//closeAndOpenDrawer();
}
Guess_Game_Interface::~Guess_Game_Interface()
{}

void Guess_Game_Interface::setName(std::string name)
{
	this->name = name;
}

std::string Guess_Game_Interface::getName()
{
	return this->name;
}

void Guess_Game_Interface::updatePlayerList()
{
	this->getPLayers();
}

void Guess_Game_Interface::getPLayers()
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
		item1->setFlags(item1->flags() ^ Qt::ItemIsEditable);
		model->appendRow(item1);

	}

	ui.playerList->setModel(model);


}

void Guess_Game_Interface::getChatAndDelete()
{
	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/get_chat" });
	auto chat = crow::json::load(response.text);

	// Itera?i prin mesaje ?i face?i cereri DELETE pentru fiecare
	for (const auto& message : chat)
	{
		std::string content = message["content"].s(); 
		DeleteChatMessage(content);
	}
}

void Guess_Game_Interface::DeleteChatMessage(const std::string& contentToDelete)
{
	cpr::Response deleteResponse = cpr::Delete(cpr::Url{ "http://localhost:18080/chat" },cpr::Parameters{ {"Message", contentToDelete} });
}

void Guess_Game_Interface::updateChat()
{
	auto responseMessages = cpr::Get(cpr::Url{ "http://localhost:18080/get_chat" });
	auto responseRows = crow::json::load(responseMessages.text);
	ui.chatDisplay->clear();
	for (const auto& responseRow : responseRows)
	{
		std::string message;
		std::string mess = std::string(responseRow["Message"]);
		message = message + std::string(responseRow["Username"]);
		message += ": ";
		message += mess;
		QString qstrMessage;

		for (auto c : message)
			qstrMessage.push_back(c);
		ui.chatDisplay->append(qstrMessage);
	}
	
	
}

void Guess_Game_Interface::sendMessage()
{
	QString message = ui.messageInput->text();
	if (!message.isEmpty())
	{
		/*ui.chatDisplay->append("You: " + message);*/
		ui.messageInput->clear();
		cpr::Response sendMessageResponse = cpr::Put(cpr::Url{ "http://localhost:18080/chat" }, cpr::Parameters{ { "Message" ,message.toStdString()},
		{"Username",this->getName()}});
	}
}
void Guess_Game_Interface::setWord()
{
	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/get_random_word" });
	auto jsonword = crow::json::load(response.text);

	this->word = jsonword["word"].s();
	qDebug() << word;
}

//void Guess_Game_Interface::closeAndOpenDrawer()
//{
//	std::string start1 = "true";
//	auto response = cpr::Put(cpr::Url{ "http://localhost:18080/startGame" }, cpr::Parameters{ { "start", start1} });
//
//	cpr::Response response1 = cpr::Get(cpr::Url{ "http://localhost:18080/getUserType" });
//	auto interfaceTypes = crow::json::load(response1.text);
//
//	if (interfaceTypes) {
//		std::string userIsDrawer;  // Seteaz? la true dac? utilizatorul curent este desenatorul
//
//		for (const auto& interfaceType : interfaceTypes) {
//			std::string playerName = interfaceType["name"].s();
//			std::string boolValue = interfaceType["guesser"].s();
//
//			if (playerName == this->getName()) {
//				userIsDrawer = boolValue;
//				break;
//			}
//		}
//
//		QWidgetList topLevelWidgets = QApplication::topLevelWidgets();
//		for (int i = 0; i < topLevelWidgets.size(); ++i) {
//			QWidget* widget = topLevelWidgets.at(i);
//			if (widget->objectName() == "Drawer_Game_Interface" || widget->objectName() == "Guess_Game_Interface") {
//				widget->close();  // Închide widget-ul
//				widget->deleteLater();  // Amân? ?tergerea widget-ului
//			}
//		}
//		if (userIsDrawer == "true") {
//			Drawer_Game_Interface* draw = new Drawer_Game_Interface(this);
//			draw->setName(this->getName());
//			draw->show();
//		}
//		else if (userIsDrawer == "false") {
//			Guess_Game_Interface* guesser = new Guess_Game_Interface(this);
//			guesser->setName(this->getName());
//			guesser->show();
//		}
//		else if (userIsDrawer == "end") {
//			Lobby_Interface* lobby = new Lobby_Interface(this);
//			lobby->setName(this->getName());
//			lobby->show();
//		}
//	}
//}