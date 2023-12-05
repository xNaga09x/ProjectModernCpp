#include "Login_Interface.h"

Login_Interface::Login_Interface(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    Lobby = nullptr;
}

Login_Interface::~Login_Interface()
{}

std::string Login_Interface::getName() const
{
    return this->name;
}

void Login_Interface::on_Loggin_clicked()
{
    this->name =  ui.lineEdit->text().toStdString();
    std::string json_data = this->name;

    auto response = cpr::Post(
        cpr::Url{ "http://localhost:18080/adduser" },
        cpr::Body(json_data)
    );
    
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
