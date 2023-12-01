#pragma once

#include <QMainWindow>
#include "ui_Loggin_Interface.h"

class Loggin_Interface : public QMainWindow
{
	Q_OBJECT

public:
	Loggin_Interface(QWidget *parent = nullptr);
	~Loggin_Interface();

private:
	Ui::Loggin_InterfaceClass ui;
};
