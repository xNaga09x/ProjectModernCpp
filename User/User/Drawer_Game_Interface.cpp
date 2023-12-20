#include "Drawer_Game_Interface.h"


Drawer_Game_Interface::Drawer_Game_Interface(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	updateTimer = new QTimer(this);
	updateTimer->start(10000);

	QTimer* chatUpdateTimer = new QTimer(this);
	connect(chatUpdateTimer, SIGNAL(timeout()), this, SLOT(updateChat()));
	chatUpdateTimer->start(100);
}

Drawer_Game_Interface::~Drawer_Game_Interface()
{}

bool Drawer_Game_Interface::openImage(const QString & fileName)
{
	//aici primim o imagine din fisier si verificam sa fie minim pe marimile widget-ului
	QImage loadedImage;
	if (!loadedImage.load(fileName))
		return false;

	QSize newSize = loadedImage.size().expandedTo(size());
	resizeImage(&loadedImage, newSize);//redimensionare
	image = loadedImage;
	modified = false;
	update();//update
	return true;
}

bool Drawer_Game_Interface::saveImage(const QString& fileName, const char* fileFormat)
{
	///Creaza un obiect de tip QImage si salveaza ce este vizibil din imaginea importata si o salveaza
	//Daca totul este ok, setam modified ca si false
	QImage visibleImage = image;
	resizeImage(&visibleImage, size());

	if (visibleImage.save(fileName, fileFormat))
	{
		modified = false;
		return true;
	}
	return false;
}

void Drawer_Game_Interface::setPenColor(const QColor& newColor)
{
	//seteaza culoarea
	myPenColor = newColor;
}

void Drawer_Game_Interface::setPenWidth(int newWidth)
{
	//seteaza grosimea
	myPenWidth = newWidth;
}

void Drawer_Game_Interface::clearImage()
{
	//setam toata imaginea cu alb(255,255,255) pentru a sterge desenul curent
	image.fill(qRgb(255, 255, 255));
	modified = true;
	update();
}

void Drawer_Game_Interface::print()
{
	//Cream un obiect QPrinter HR pt output
	//In QDialog specificam dimensiunile dorite
	//Daca este acceptata dimensiunea incepem desenarea
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printdialog)
	QPrinter printer(QPrinter::HighResolution);

	QPrintDialog printDialog(&printer, this);
	if (printDialog.exec() == QDialog::Accepted) {
		QPainter painter(&printer);
		QRect rect = painter.viewport();
		QSize size = image.size();
		size.scale(rect.size(), Qt::KeepAspectRatio);
		painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
		painter.setWindow(image.rect());
		painter.drawImage(0, 0, image);
	}
#endif // QT_CONFIG(printdialog)
}

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
	connect(ui.redButton, &QPushButton::clicked, this, &Drawer_Game_Interface::redButtonClicked);
	connect(ui.blueButton, &QPushButton::clicked, this, &Drawer_Game_Interface::blueButtonClicked);
	connect(ui.yellowButton, &QPushButton::clicked, this, &Drawer_Game_Interface::yellowButtonClicked);
	connect(ui.blackButton, &QPushButton::clicked, this, &Drawer_Game_Interface::blackButtonClicked);
	connect(ui.cyanButton, &QPushButton::clicked, this, &Drawer_Game_Interface::cyanButtonClicked);
	connect(ui.greenButton, &QPushButton::clicked, this, &Drawer_Game_Interface::greenButtonClicked);
	connect(ui.limeButton, &QPushButton::clicked, this, &Drawer_Game_Interface::limeButtonClicked);
	connect(ui.pinkButton, &QPushButton::clicked, this, &Drawer_Game_Interface::pinkButtonClicked);
	connect(ui.purpleButton, &QPushButton::clicked, this, &Drawer_Game_Interface::purpleButtonClicked);
	connect(ui.brownButton, &QPushButton::clicked, this, &Drawer_Game_Interface::brownButtonClicked);
	connect(ui.orangeButton, &QPushButton::clicked, this, &Drawer_Game_Interface::orangeButtonClicked);

	connect(ui.clearButton, &QPushButton::clicked, this, &Drawer_Game_Interface::clearButtonClicked);

	connect(ui.widthSlider, &QSlider::valueChanged, this, &Drawer_Game_Interface::setPenWidth);
	ui.widthSlider->setRange(1, 10); // Seteaz? intervalul grosimii penului


	// Crea?i un obiect QPainter pentru zona de desenare
	QPainter painter(this);

	// Seta?i culoarea pentru fundalul UI-ului la albastru
	painter.fillRect(rect(), Qt::gray);

	// Defini?i regiunea permis? (rama alb?)
	int margin = 100;
	QRect allowedRegion(margin+100, margin, width() - 420, height() - 300);

	// Desena?i culoarea pentru regiunea permis? (fundalul alb)
	painter.fillRect(allowedRegion, Qt::white);

	// Excluziunea regiunii în care nu dori?i s? desena?i (culoarea albastr?)
	QRect exclusionRegion(200, 100, width() - 420, height() - 300);
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
		setGeometry(x + 70, y + 70, image.width()-10, image.height());

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

void Drawer_Game_Interface::redButtonClicked()
{

	setPenColor(Qt::red);
}

void Drawer_Game_Interface::blueButtonClicked()
{
	setPenColor(Qt::blue);

}

void Drawer_Game_Interface::yellowButtonClicked()
{
	setPenColor(Qt::yellow);

}
void Drawer_Game_Interface::blackButtonClicked()
{
	setPenColor(Qt::black);
}



void Drawer_Game_Interface::cyanButtonClicked()
{
	setPenColor(Qt::cyan);

}

void Drawer_Game_Interface::greenButtonClicked()
{

	setPenColor(Qt::darkGreen);
}

void Drawer_Game_Interface::limeButtonClicked()
{
	setPenColor(Qt::green);
}



void Drawer_Game_Interface::pinkButtonClicked()
{
	setPenColor(Qt::magenta);


}

void Drawer_Game_Interface::purpleButtonClicked()
{
	setPenColor(QColor(148, 0, 211)); // RGB values for pink color

}

void Drawer_Game_Interface::brownButtonClicked()
{
	setPenColor(QColor(165, 42, 42)); // RGB values for pink color

}

void Drawer_Game_Interface::orangeButtonClicked()
{
	
	setPenColor(QColor(255, 165, 0));
}

void Drawer_Game_Interface::clearButtonClicked()
{
	//setam toata imaginea cu alb(255,255,255) pentru a sterge desenul curent
	image.fill(qRgb(255, 255, 255));
	modified = true;
	update();

}

void Drawer_Game_Interface::DeleteChatMessage(const std::string& contentToDelete)
{
	cpr::Response deleteResponse = cpr::Delete(cpr::Url{ "http://localhost:18080/chat" }, cpr::Parameters{ {"Message", contentToDelete} });
}

void Drawer_Game_Interface::getChatAndDelete()
{
		cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:18080/get_chat" });
		auto chat = crow::json::load(response.text);

		// Itera?i prin mesaje ?i face?i cereri DELETE pentru fiecare
		for (const auto& message : chat)
		{
			std::string content = message["content"].s();
			DeleteChatMessage(content);
		}
}

void Drawer_Game_Interface::updatePlayerList()
{
}

void Drawer_Game_Interface::getPLayers()
{
}

void Drawer_Game_Interface::updateChat()
{
	auto responseMessages = cpr::Get(cpr::Url{ "http://localhost:18080/get_chat" });
	auto responseRows = crow::json::load(responseMessages.text);
	ui.chatDisplayDraw->clear();
	for (const auto& responseRow : responseRows)
	{
		std::string message;
		std::string mess = std::string(responseRow["Message"]);
		message = message + std::string(responseRow["Username"]);
		message += ": ";
		message += mess;
		QString qstrMessage;

		for (auto c : message)
			qstrMessage.push_back(c);
		ui.chatDisplayDraw->append(qstrMessage);
	}
}





