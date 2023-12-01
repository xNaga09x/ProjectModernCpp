#pragma once

#include <QMainWindow>
#include "ui_Register_Interface.h"

class Register_Interface : public QMainWindow
{
	Q_OBJECT

public:
	Register_Interface(QWidget *parent = nullptr);
	~Register_Interface();

private:
	Ui::Register_InterfaceClass ui;
};
