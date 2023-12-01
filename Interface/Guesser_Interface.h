#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Guesser_Interface.h"
#include"Loggin_Interface.h"
#include"Register_Interface.h"
class Guesser_Interface : public QMainWindow
{
    Q_OBJECT

public:
    Guesser_Interface(QWidget *parent = nullptr);
    ~Guesser_Interface();
public slots:
    void on_Loggin_clicked();
    void on_Register_clicked();
private:
    Ui::Guesser_InterfaceClass ui;
    Loggin_Interface* Log;
    Register_Interface* Reg;
};
