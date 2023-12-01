#include "Guesser_Interface.h"

Guesser_Interface::Guesser_Interface(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    Log = nullptr;
    Reg = nullptr;
}

Guesser_Interface::~Guesser_Interface()
{}
void Guesser_Interface::on_Loggin_clicked()
{
    this->close();
    Log = new Loggin_Interface(this);
    Log->show();
}
void Guesser_Interface::on_Register_clicked()
{
    this->close();
    Reg = new Register_Interface(this);
    Reg->show();
}