#include "ColorWindow.h"

ColorWindow::ColorWindow(QWidget* parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(500, 100);
}

ColorWindow::~ColorWindow()
{
}