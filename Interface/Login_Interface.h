#pragma once

#include "ui_Login_Interface.h"
#include <QMessageBox>
#include <QPalette>
#include <QPixmap>
#include <QtWidgets/QMainWindow>

class Login_Interface : public QMainWindow
{
    Q_OBJECT

public:
    Login_Interface(QWidget *parent = nullptr);
    ~Login_Interface();

private:
    Ui::Login_InterfaceClass ui;
};
