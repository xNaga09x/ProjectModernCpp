#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), drawArea(new DrawArea(this))
{
    //In constructor cream o zona de desenare in widgetul nostru
    setCentralWidget(drawArea);

    createActions();
    createMenus();

    setWindowTitle(tr("Gartic"));
    resize(500, 500);
    //ui.setupUi(this);
}

MainWindow::~MainWindow()
{}

void MainWindow::closeEvent(QCloseEvent* event)
{
    //Permite user-ului sa inchida pagina si permite sa salveze eventuale modificari nesalvate
    if (maybeSave())
        event->accept();
    else
        event->ignore();
}

void MainWindow::open()
{
    //Permitem salvarea modificarilor inaintea afisarii unei noi imagini, iar apoi ii cerem sa aleaga o imagine pe care o incarcam
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), QDir::currentPath());
        if (!fileName.isEmpty())
            drawArea->openImage(fileName);
    }
}

void MainWindow::save()
{
    //Permite salvarea cu un anumit format
    QAction* action = qobject_cast<QAction*>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::penColor()
{
    //Functia ne lasa sa alegem o noua culoarea
    QColor newColor = QColorDialog::getColor(drawArea->penColor());
    if (newColor.isValid())
        drawArea->setPenColor(newColor);
}

void MainWindow::penWidth()
{
    //Permite selectarea unei noi grosimi, aceasta este introdusa de utilizator, iar daca acest selecteaza o culoare, ok este true
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Gartic"),
        tr("Select pen width:"),
        drawArea->penWidth(),
        1, 50, 1, &ok);
    if (ok)
        drawArea->setPenWidth(newWidth);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Gartic"),
        tr("<p>The <b>Gartic</b> example shows how to use QMainWindow as the "
            "base widget for an application, and how to reimplement some of "
            "QWidget's event handlers to receive the events generated for "
            "the application's widgets:</p><p> We reimplement the mouse event "
            "handlers to facilitate drawing, the paint event handler to "
            "update the application and the resize event handler to optimize "
            "the application's appearance. In addition we reimplement the "
            "close event handler to intercept the close events before "
            "terminating the application.</p><p> The example also demonstrates "
            "how to use QPainter to draw an image in real time, as well as "
            "to repaint widgets.</p>"));
}

void MainWindow::createActions()
{
    //Aici cream actiunile meniului si le legam de slot-urile aferente.
    //Apelam QAction::setData() pentru a obtine mai tarziu datele cu ajutorul QAction::data()
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    const QList<QByteArray> imageFormats = QImageWriter::supportedImageFormats();
    for (const QByteArray& format : imageFormats) {
        QString text = tr("%1...").arg(QString::fromLatin1(format).toUpper());

        QAction* action = new QAction(text, this);
        action->setData(format);
        connect(action, &QAction::triggered, this, &MainWindow::save);
        saveAsActs.append(action);
    }

    printAct = new QAction(tr("&Print..."), this);
    connect(printAct, &QAction::triggered, drawArea, &DrawArea::print);

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, &QAction::triggered, this, &MainWindow::close);

    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, &QAction::triggered, this, &MainWindow::penColor);

    penWidthAct = new QAction(tr("Pen &Width..."), this);
    connect(penWidthAct, &QAction::triggered, this, &MainWindow::penWidth);

    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, &QAction::triggered,
        drawArea, &DrawArea::clearImage);

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void MainWindow::createMenus()
{
    //Aici retragem datele salvate anterior si apoi adaugam restul actiunilor
    //In plus adauga un meniu
    saveAsMenu = new QMenu(tr("&Save As"), this);
    for (QAction* action : std::as_const(saveAsActs))
        saveAsMenu->addAction(action);

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(helpMenu);
}

bool MainWindow::maybeSave()
{
    //Verificam daca sunt modificari nesalvate, daca sunt va da un avertisment
    if (drawArea->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Gartic"),
            tr("The image has been modified.\n"
                "Do you want to save your changes?"),
            QMessageBox::Save | QMessageBox::Discard
            | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return saveFile("png");
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

bool MainWindow::saveFile(const QByteArray& fileFormat)
{
    //Salveaza imaginea sum un fisier cu numele dorit
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
        initialPath,
        tr("%1 Files (*.%2);;All Files (*)")
        .arg(QString::fromLatin1(fileFormat.toUpper()))
        .arg(QString::fromLatin1(fileFormat)));
    if (fileName.isEmpty())
        return false;
    return drawArea->saveImage(fileName, fileFormat.constData());
}