#include "Guesser_Interface.h"

Guesser_Interface::Guesser_Interface(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    Lobby = nullptr;
}

Guesser_Interface::~Guesser_Interface()
{}
void Guesser_Interface::on_Loggin_clicked()
{
    this->close();
    Lobby = new Lobby_Interface(this);
    Lobby->show();
}
void Guesser_Interface::on_Register_clicked()
{
    this->close();
    Lobby = new Lobby_Interface(this);
    Lobby->show();
}