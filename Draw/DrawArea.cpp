#include "DrawArea.h"

DrawArea::DrawArea(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
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

    if (visibleImage.save(fileName, fileFormat)) {
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