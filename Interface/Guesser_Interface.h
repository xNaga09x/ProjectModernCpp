#pragma once

#include <QMainWindow>
#include "ui_Guesser_Interface.h"

class Guesser_Interface : public QMainWindow
{
	Q_OBJECT

public:
	Guesser_Interface(QWidget *parent = nullptr);
	~Guesser_Interface();

private:
	Ui::Guesser_InterfaceClass ui;
};
