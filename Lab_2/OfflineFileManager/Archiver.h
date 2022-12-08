#pragma once

#include <QMainWindow>
#include "ui_Archiver.h"

class Archiver : public QMainWindow
{
	Q_OBJECT

public:
	Archiver(QWidget *parent = nullptr);
	~Archiver();

private:
	Ui::ArchiverClass ui;
};
