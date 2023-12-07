#include "User.h"

User::User(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    Lobby = nullptr;
}

User::~User()
{}
std::string User::getName() const
{
    return this->name;
}

void User::on_Loggin_clicked()
{
    //posibil de verificat daca apasa pe butonul de register/login sa se vada daca exista acel user , daca nu sa se verifice cand se da register
    //daca exista in database , daca nu , se creeaza in database . Daca nu verifica nimeni , suntem safe.
    this->name = ui.lineEdit->text().toStdString();

    std::string json_data = this->name;

    auto response = cpr::Post(
        cpr::Url{ "http://localhost:18080/adduser" },
        cpr::Body(json_data)
    );

    this->close();
    Lobby = new Lobby_Interface(this);
    Lobby->show();
}
void User::on_Register_clicked()
{
    this->close();
    Lobby = new Lobby_Interface(this);
    Lobby->show();
}