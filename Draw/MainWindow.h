#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <qdir.h>
#include <qfiledialog.h>
#include <qcolordialog.h>
#include <qinputdialog.h>
#include <qmessagebox.h>
#include <qimagewriter.h>
#include "DrawArea.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void open();
    void save();
    void penColor();
    void penWidth();
    void about();

private:
    //Ui::MainWindowClass ui;

    void createActions();
    void createMenus();
    bool maybeSave();   //verifica daca sunt modificari nesalvate
    bool saveFile(const QByteArray& fileFormat);    //permitem salvarea desenului

    DrawArea* drawArea;

    QMenu* saveAsMenu;
    QMenu* fileMenu;
    QMenu* optionMenu;
    QMenu* helpMenu;

    QAction* openAct;
    QList<QAction*> saveAsActs;
    QAction* exitAct;
    QAction* penColorAct;
    QAction* penWidthAct;
    QAction* printAct;
    QAction* clearScreenAct;
    QAction* aboutAct;
    QAction* aboutQtAct;
};
