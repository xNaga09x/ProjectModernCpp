#pragma once

#include <QMainWindow>
#include "ui_Guess_Game_Interface.h"

class Guess_Game_Interface : public QMainWindow
{
	Q_OBJECT

public:
	Guess_Game_Interface(QWidget *parent = nullptr);
	~Guess_Game_Interface();

private:
	Ui::Guess_Game_InterfaceClass ui;
};
