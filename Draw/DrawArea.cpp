#include "DrawArea.h"

DrawArea::DrawArea(QWidget *parent)
    
{
	//ui.setupUi(this);
	setAttribute(Qt::WA_StaticContents); //setam atributul StaticContents pentru a fixa continutul widgetului in coltul din stanga sus
										 //se fol. pentru a optimiza redimensionarile
}

DrawArea::~DrawArea()
{}

bool DrawArea::openImage(const QString& fileName)
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

bool DrawArea::saveImage(const QString& fileName, const char* fileFormat)
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

void DrawArea::setPenColor(const QColor& newColor)
{
    //seteaza culoarea
    myPenColor = newColor;
}

void DrawArea::setPenWidth(int newWidth)
{
    //seteaza grosimea
    myPenWidth = newWidth;
}

void DrawArea::clearImage()
{
    //setam toata imaginea cu alb(255,255,255) pentru a sterge desenul curent
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

void DrawArea::mousePressEvent(QMouseEvent* event)
{
    //verificam ce buton s-a apasat si daca este click stanga setam scribbling drept true
    //tinem minte pozitia
    if (event->button() == Qt::LeftButton) 
    {
        lastPoint = event->position().toPoint();
        scribbling = true;
    }
}

void DrawArea::mouseMoveEvent(QMouseEvent* event)
{
    //deseneaza linia cat timp este apasat butonul
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->position().toPoint());
}

void DrawArea::mouseReleaseEvent(QMouseEvent* event)
{
    //se opreste desenarea
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->position().toPoint());
        scribbling = false;
    }
}

void DrawArea::paintEvent(QPaintEvent* event)
{
    //Cream un obiect de tip QPainter pentru zona de desenare si desenam
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void DrawArea::resizeEvent(QResizeEvent* event)
{
    // Redimensiona?i imaginea numai dac? widget-ul devine mai mare decât dimensiunea imaginii
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() - 400, image.width());
        int newHeight = qMax(height() -150, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));

        // Calcula?i pozi?ia central? în widget
        int x = (width() - image.width()) / 2;
        int y = (height() - image.height()) / 2;

        // Actualiza?i pozi?ia zonei de desenare
        setGeometry(x, y, image.width(), image.height());

        update();
    }

    QWidget::resizeEvent(event);
}

void DrawArea::drawLineTo(const QPoint& endPoint)
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

void DrawArea::resizeImage(QImage* image, const QSize& newSize)
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

void DrawArea::print()
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