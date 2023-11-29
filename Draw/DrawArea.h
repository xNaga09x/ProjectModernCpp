#pragma once

#include <QMainWindow>
#include "ui_DrawArea.h"

class DrawArea : public QMainWindow
{
	Q_OBJECT

public:
	DrawArea(QWidget *parent = nullptr);
	~DrawArea();

private:
	Ui::DrawAreaClass ui;
};
