#include "Guesser_Interface.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Guesser_Interface w;
    w.show();
    return a.exec();
}
