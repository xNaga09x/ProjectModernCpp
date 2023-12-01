#include "Guesser_Interface.h"

Guesser_Interface::Guesser_Interface(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    Log = nullptr;
}

Guesser_Interface::~Guesser_Interface()
{}
void Guesser_Interface::on_Loggin_clicked()
{
    this->close();
    Log = new Loggin_Interface(this);
    Log->show();
}