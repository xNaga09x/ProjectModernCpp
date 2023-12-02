#pragma once

#include <QMainWindow>
#include "ui_Lobby_Interface.h"
#include "Guess_Game_Interface.h"

class Lobby_Interface : public QMainWindow
{
	Q_OBJECT

public:
	Lobby_Interface(QWidget *parent = nullptr);
	~Lobby_Interface();

public slots:
	void on_start_game_clicked();
private:
	Ui::Lobby_InterfaceClass ui;
	Guess_Game_Interface* guesser;
};
