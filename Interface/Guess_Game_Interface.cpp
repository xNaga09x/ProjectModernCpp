#include "Guess_Game_Interface.h"

Guess_Game_Interface::Guess_Game_Interface(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowTitle("Main Game");
	
	// Connect signals and slots
	connect(ui.sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
} 

Guess_Game_Interface::~Guess_Game_Interface()
{}


void Guess_Game_Interface::sendMessage()
{
	QString message = ui.messageInput->text();
	if (!message.isEmpty())
	{
		ui.chatDisplay->append("You: " + message);

		ui.messageInput->clear();
	}
}
// De retinut ca mesajele trebuie trimise catre server ca sa fie luate inapoi de catre toti ceilalti jucatori .
