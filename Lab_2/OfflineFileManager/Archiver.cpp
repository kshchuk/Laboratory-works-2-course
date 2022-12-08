#include "Archiver.h"

Archiver::Archiver(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->setCentralWidget(ui.layoutWidget);

}

Archiver::~Archiver()
{}
