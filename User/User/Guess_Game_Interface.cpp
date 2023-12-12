#include "Guess_Game_Interface.h"

Guess_Game_Interface::Guess_Game_Interface(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("Main Game");

	getPLayers();
	// Connect signals and slots
	connect(ui.sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));



}

Guess_Game_Interface::~Guess_Game_Interface()
{}

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

		model->appendRow(item1);

	}

	ui.playerList->setModel(model);


}


void Guess_Game_Interface::sendMessage()
{
	QString message = ui.messageInput->text();

	if (!message.isEmpty())
	{
		ui.chatDisplay->append("You: " + message);
		ui.messageInput->clear();
		cpr::Response sendMessageResponse = cpr::Post(cpr::Url{ "http://localhost:18080/chat" }, cpr::Body{ message.toStdString()});
	}
}
