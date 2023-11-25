#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Login_Interface.h"
#include <QPixmap>
#include<QPalette>
#include<QMessageBox>
class Login_Interface : public QMainWindow
{
    Q_OBJECT

public:
    Login_Interface(QWidget *parent = nullptr);
    ~Login_Interface();

private:
    Ui::Login_InterfaceClass ui;
};
