#include "Login_Interface.h"

Login_Interface::Login_Interface(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    Lobby = nullptr;
}

Login_Interface::~Login_Interface()
{}
void Login_Interface::on_Loggin_clicked()
{
    this->close();
    Lobby = new Lobby_Interface(this);
    Lobby->show();
}
void Login_Interface::on_Register_clicked()
{
    this->close();
    Lobby = new Lobby_Interface(this);
    Lobby->show();
}
