#include "Archiver.h"

#include <QFileDialog>

#include "ArchiverLogic.h"


Archiver::Archiver(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->setCentralWidget(ui.centralWidget);
	ui.listWidget->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(ui.pushButton, &QPushButton::clicked, this, &Archiver::SelectFiles);
	connect(ui.pushButton_2, &QPushButton::clicked, this, &Archiver::SelectArchive);
	connect(ui.pushButton_7, &QPushButton::clicked, this, &Archiver::ClearAll);
	connect(ui.pushButton_5, &QPushButton::clicked, this, &Archiver::ArchiveAll);
	connect(ui.pushButton_6, &QPushButton::clicked, this, &Archiver::UnarchiveAll);
}

Archiver::~Archiver()
{}

void Archiver::SelectFiles()
{
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::ExistingFiles);
	if (dialog.exec())
		selected += dialog.selectedFiles();
	UpdateSelected();
}

void Archiver::SelectArchive()
{
    QString fileName = QFileDialog::getOpenFileName(this, ("Open Archive"),
        "", ("Archive (*.zst)"));

	selected += fileName;
	UpdateSelected();
}

void Archiver::ArchiveAll()
{
	QString fileName = QFileDialog::getExistingDirectory(this, "");
	
	ArchiverLogic* arch = new ArchiverLogic();

	std::vector<std::string> sel; for (auto file : selected) sel.push_back(file.toStdString());

	arch->set_files(sel);
	arch->set_destination(fileName.toStdString());
	arch->ZSTDCompress();
}

void Archiver::UnarchiveAll()
{
	QString fileName = QFileDialog::getExistingDirectory(this, "");

	ArchiverLogic* arch = new ArchiverLogic();

	std::vector<std::string> sel; for (auto file : selected) sel.push_back(file.toStdString());

	arch->set_files(sel);
	arch->set_destination(fileName.toStdString());
	arch->ZSTDDecompress();
}

void Archiver::AddToList(QString path)
{
	selected.append(path);
	UpdateSelected();
}

void Archiver::ClearAll()
{
	selected.clear();
	ui.listWidget->clear();
}

void Archiver::UpdateSelected()	
{
    ui.listWidget->clear();
    foreach(auto elem, selected) {
        QFileInfo info(elem);
        QListWidgetItem* item = new QListWidgetItem(icons.icon(info), info.fileName());
        ui.listWidget->addItem(item);
    }
}
