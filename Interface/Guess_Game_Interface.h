#pragma once

#include <QMainWindow>
#include "ui_Guess_Game_Interface.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

class Guess_Game_Interface : public QMainWindow
{
	Q_OBJECT

public:
	Guess_Game_Interface(QWidget *parent = nullptr);
	~Guess_Game_Interface();

private slots:
	void sendMessage();


private:
	Ui::Guess_Game_InterfaceClass ui;

}; 
