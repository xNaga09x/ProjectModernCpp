#include "User.h"

User::User(QWidget* parent)
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

	this->name = ui.lineEdit->text().toStdString();
	auto usersResponse = cpr::Get(cpr::Url{ "http://localhost:18080/users" });
	std::string json_data = this->name;

	crow::json::rvalue usersJson = crow::json::load(usersResponse.text);
	
	auto found = usersResponse.text.find(this->name);

	if(found==std::string::npos)
	{
		auto response = cpr::Post(
			cpr::Url{ "http://localhost:18080/adduser" },
			cpr::Body(json_data)
		);
	}

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