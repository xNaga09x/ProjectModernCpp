#include "ColorWindow.h"
#include <qdebug.h>
#ifndef COLORWINDOW_CPP
#define COLORWINDOW_CPP

ColorWindow::ColorWindow(QWidget* parent)
    : QWidget(parent)
{
    qDebug() << "ColorWindow constructor called";
    // Inițializări și configurări pentru fereastra suplimentară
}

ColorWindow::~ColorWindow()
{
    qDebug() << "ColorWindow destructor called";
    // Eliberează resurse la distrugerea ferestrei suplimentare
}

#endif // COLORWINDOW_CPP