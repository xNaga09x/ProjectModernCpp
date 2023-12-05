#include "Login_Interface.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login_Interface w;
    w.show();
    return a.exec();


	/*Login_Interface logininterface;
	std::string name = logininterface.getName();*/

    
}
