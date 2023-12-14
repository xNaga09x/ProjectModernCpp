#include "Drawer_Game_Interface.h"

Drawer_Game_Interface::Drawer_Game_Interface(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Drawer_Game_Interface::~Drawer_Game_Interface()
{}

void Drawer_Game_Interface::drawLineTo(const QPoint & endPoint)
{
	//Desenam o linie de la ultima pozitie pana la pozitia curenta
	//Setam modificat ca true
	//Resetam ultima pozitie pentru a continua din punctul in care ne-am oprit
	//Updatam imaginea
	QPainter painter(&image);
	painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
		Qt::RoundJoin));
	painter.drawLine(lastPoint, endPoint);
	modified = true;

	int rad = (myPenWidth / 2) + 2;
	update(QRect(lastPoint, endPoint).normalized()
		.adjusted(-rad, -rad, +rad, +rad));
	lastPoint = endPoint;
}

void Drawer_Game_Interface::resizeImage(QImage* image, const QSize& newSize)
{
	//Pentru redimensionarea imaginii cream o noua imagine alba cu dimensiunea dorita si uploadam vechea imagine 
	if (image->size() == newSize)
		return;

	QImage newImage(newSize, QImage::Format_RGB32);
	newImage.fill(qRgb(255, 255, 255));
	QPainter painter(&newImage);
	painter.drawImage(QPoint(0, 0), *image);
	*image = newImage;
}
