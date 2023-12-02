#pragma once

#include <QMainWindow>
#include "ui_Lobby_Interface.h"

class Lobby_Interface : public QMainWindow
{
	Q_OBJECT

public:
	Lobby_Interface(QWidget *parent = nullptr);
	~Lobby_Interface();

private:
	Ui::Lobby_InterfaceClass ui;
};
