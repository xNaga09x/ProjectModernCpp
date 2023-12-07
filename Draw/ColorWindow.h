#pragma once
#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>

class ColorWindow: public QMainWindow
{
    Q_OBJECT

public:
    ColorWindow(QWidget* parent = nullptr);
    ~ColorWindow();

private slots:
    void colorButtonClicked();

private:
    void setupColorPalette();

    QVBoxLayout* mainLayout;
    QGridLayout* colorGridLayout;
    QPushButton* colorButtons[10];  // Poți ajusta numărul de culori aici
    QString colorNames[10];
};