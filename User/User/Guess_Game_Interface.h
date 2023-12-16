#pragma once

#include <QMainWindow>
#include "ui_Guess_Game_Interface.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include <qurl.h>
#include <cpr/cpr.h>
#include <crow.h>
#include <fstream>

#include <QTimer>
#include <QApplication>
#include <QListView>
#include <QStandardItemModel>
#include <QStandardItem>



class Guess_Game_Interface : public QMainWindow
{
	Q_OBJECT

public:
	Guess_Game_Interface(QWidget* parent = nullptr);
	~Guess_Game_Interface();
	void setName(std::string name);
	std::string getName();

private slots:
	void sendMessage();
	void updatePlayerList();
	void getPLayers();
	void getChatAndDelete();
	void DeleteChatMessage(const std::string& contentToDelete); 

private:
	Ui::Guess_Game_InterfaceClass ui;
	std::string name;
	QTimer* updateTimer; 

};
