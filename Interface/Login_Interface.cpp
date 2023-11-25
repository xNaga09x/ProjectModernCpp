#include "Login_Interface.h"

Login_Interface::Login_Interface(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QPushButton* backgroundColourButton;
    QColor* backgroundColour;
    backgroundColour->setRgb(0, 0, 0); //example colour, I could later manage to utilize this variable with a QColorDialog
}

Login_Interface::~Login_Interface()
{}
