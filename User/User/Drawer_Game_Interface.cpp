#include "Drawer_Game_Interface.h"

Drawer_Game_Interface::Drawer_Game_Interface(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Drawer_Game_Interface::~Drawer_Game_Interface()
{}

void Drawer_Game_Interface::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		// Verifica?i dac? punctul de ap?sare a butonului este în interiorul unei regiuni
		if (isPointInsideAllowedRegion(event->pos()))
		{
			lastPoint = event->pos();
			scribbling = true;
		}
	}
}

void Drawer_Game_Interface::mouseMoveEvent(QMouseEvent* event)
{
	// Desen?m linia doar dac? mi?carea mouse-ului are loc în interiorul regiunii permise
	if ((event->buttons() & Qt::LeftButton) && scribbling && isPointInsideAllowedRegion(event->pos()))
		drawLineTo(event->pos());
}

void Drawer_Game_Interface::mouseReleaseEvent(QMouseEvent* event)
{
	// Se opre?te desenarea numai dac? s-a efectuat desenarea ?i dac? punctul curent este în interiorul regiunii permise
	if (event->button() == Qt::LeftButton && scribbling && isPointInsideAllowedRegion(event->pos()))
	{
		drawLineTo(event->pos());
		scribbling = false;
	}
}

bool Drawer_Game_Interface::isPointInsideAllowedRegion(const QPoint& point)
{
	// Defini?i regiunea permis? (de exemplu, o margine de 20 de pixeli)
	QRect allowedRegion(100, 100, width() - 300, height() - 300);

	// Verifica?i dac? punctul este în interiorul regiunii permise
	return allowedRegion.contains(point);
}

void Drawer_Game_Interface::paintEvent(QPaintEvent* event)
{
	// Crea?i un obiect QPainter pentru zona de desenare
	QPainter painter(this);

	// Seta?i culoarea pentru fundalul UI-ului la albastru
	painter.fillRect(rect(), Qt::gray);

	// Defini?i regiunea permis? (rama alb?)
	int margin = 100;
	QRect allowedRegion(margin, margin, width() - 300, height() - 300);

	// Desena?i culoarea pentru regiunea permis? (fundalul alb)
	painter.fillRect(allowedRegion, Qt::white);

	// Excluziunea regiunii în care nu dori?i s? desena?i (culoarea albastr?)
	QRect exclusionRegion(100, 100, width() - 300, height() - 300);
	painter.fillRect(exclusionRegion, Qt::blue);

	// Desena?i imaginea în afara regiunii excluse (în restul zonei albe)
	QRect dirtyRect = event->rect();
	QRect imageRect = image.rect();
	QRect intersection = dirtyRect.intersected(exclusionRegion);

	if (!intersection.isEmpty()) {
		// Desena?i imaginea în regiunea alb? r?mas?
		QRect allowedRect = dirtyRect.intersected(allowedRegion);
		painter.drawImage(allowedRect, image, allowedRect);
	}
}

void Drawer_Game_Interface::resizeEvent(QResizeEvent* event)
{
	// Redimensiona?i imaginea numai dac? widget-ul devine mai mare decât dimensiunea imaginii
	if (width() > image.width() || height() > image.height()) {
		int newWidth = qMax(width(), image.width());
		int newHeight = qMax(height(), image.height());
		resizeImage(&image, QSize(newWidth, newHeight));

		// Calcula?i pozi?ia central? în widget
		int x = (width() - image.width()) / 2;
		int y = (height() - image.height()) / 2;

		// Actualiza?i pozi?ia zonei de desenare
		setGeometry(x + 30, y + 30, image.width(), image.height());

		update();
	}
	//setGeometry(20,20, image.width(), image.height());
	update();
	QWidget::resizeEvent(event);
}

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
