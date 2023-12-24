#include "Guess_Game_Interface.h"

Guess_Game_Interface::Guess_Game_Interface(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("Main Game");

	updateTimer = new QTimer(this); 
	getPLayers(); 
	// Connect signals and slots
	connect(updateTimer, SIGNAL(timeout()), this, SLOT(updatePlayerList()));
	connect(ui.sendButton, SIGNAL(clicked()), this, SLOT(sendMessage())); 

	updateTimer->start(10000);

	QTimer* chatUpdateTimer = new QTimer(this); 
	connect(chatUpdateTimer, SIGNAL(timeout()), this, SLOT(updateChat())); 
	chatUpdateTimer->start(3000); 
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
