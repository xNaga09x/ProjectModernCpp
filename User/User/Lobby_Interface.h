#pragma once

#include <QMainWindow>
#include "ui_Lobby_Interface.h"
#include "Guess_Game_Interface.h"
#include "Drawer_Game_Interface.h"

#include <cpr/cpr.h>
#include <crow.h>
#include <fstream>


#include <QApplication>
#include <QListView>
#include <QStandardItemModel>
#include <QStandardItem>


class Lobby_Interface : public QMainWindow
{
	Q_OBJECT

public:
	Lobby_Interface(QWidget* parent = nullptr);
	~Lobby_Interface();
	void setName(std::string name);
	std::string getName();

public slots:
	void on_start_game_clicked();
	void on_drawButton_clicked();

	void getPLayers();
	void openInterface(bool type);

private:
	Ui::Lobby_InterfaceClass ui;
	Guess_Game_Interface* guesser;
	Drawer_Game_Interface* draw;
	std::string name;

};



