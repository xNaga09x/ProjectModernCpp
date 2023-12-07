#include "Lobby_Interface.h"

Lobby_Interface::Lobby_Interface(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	guesser = nullptr;

}

Lobby_Interface::~Lobby_Interface()
{}

void Lobby_Interface::on_start_game_clicked()
{
	this->close();
	guesser = new Guess_Game_Interface(this);
	guesser->show();
}