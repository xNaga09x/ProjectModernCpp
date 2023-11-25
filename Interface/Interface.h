#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Interface.h"

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    Interface(QWidget *parent = nullptr);
    ~Interface();

private:
    Ui::InterfaceClass ui;
};
