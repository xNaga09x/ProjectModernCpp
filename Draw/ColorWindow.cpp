#include "ColorWindow.h"

ColorWindow::ColorWindow(QWidget* parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(300, 200);

    mainLayout = new QVBoxLayout(this);
    colorGridLayout = new QGridLayout();

    setupColorPalette();

    mainLayout->addLayout(colorGridLayout);
    setLayout(mainLayout);

    colorNames[0] = "Red";
    colorNames[1] = "Green";
    colorNames[2] = "Blue";
    colorNames[3] = "Yellow";
    colorNames[4] = "Cyan";
    colorNames[5] = "Magenta";
    colorNames[6] = "Black";
    colorNames[7] = "White";
    colorNames[8] = "Gray";
    colorNames[9] = "Orange";
}

ColorWindow::~ColorWindow()
{
}

void ColorWindow::setupColorPalette()
{
    // Definirea culorilor disponibile
    QString colorNames[] = { "Red", "Green", "Blue", "Yellow", "Cyan", "Magenta", "Black", "White", "Gray", "Orange" };

    for (int i = 0; i < 10; ++i)
    {
        colorButtons[i] = new QPushButton(colorNames[i]);
        colorButtons[i]->setFixedSize(40, 40);  // Ajustează dimensiunea butoanelor în funcție de necesități
        colorButtons[i]->setStyleSheet(QString("background-color: %1").arg(colorNames[i].toLower()));
        colorButtons[i]->setCheckable(true);

        connect(colorButtons[i], &QPushButton::clicked, this, &ColorWindow::colorButtonClicked);

        colorGridLayout->addWidget(colorButtons[i], i / 5, i % 5);
    }
}

void ColorWindow::colorButtonClicked()
{
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());

    if (clickedButton)
    {
        // Obține culoarea butonului și folosește-o pentru desenare
        QColor selectedColor = clickedButton->palette().button().color();
        // Implementează logica pentru a utiliza această culoare în desen sau unde ai nevoie
    }
}