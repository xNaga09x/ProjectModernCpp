#pragma once
#include <QWidget>
#include <QMainWindow>

class ColorWindow: public QMainWindow
{
    Q_OBJECT

public:
    ColorWindow(QWidget* parent = nullptr);
    ~ColorWindow();

};