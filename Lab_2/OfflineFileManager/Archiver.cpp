#include "Archiver.h"

#include <QFileDialog>

Archiver::Archiver(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->setCentralWidget(ui.widget);
	ui.listWidget->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(ui.pushButton, &QPushButton::clicked, this, &Archiver::SelectFiles);
	connect(ui.pushButton_2, &QPushButton::clicked, this, &Archiver::SelectArchive);
	connect(ui.pushButton_7, &QPushButton::clicked, this, &Archiver::ClearAll);
	connect(ui.pushButton_5, &QPushButton::clicked, this, &Archiver::ArchiveAll);
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
        "", ("Archive (*.lz *.uu *.lrz *.lzo *.lz4 *.gz *.bz2 *.lzma *.xz *.cpio *.shar *.tar *.tar.gz *.tar.grz *.tar.xz *.tar.lzo *.tar.lzma *.tar.lz *.tar.lrz *.tar.lz4 *.tar.Z *.iso *.zip *.ar *.xar *.7z)"));
	
	archive = new LibArchiveQt(fileName);
	
	foreach(ArchiveEntry * ae, archive->listArchive()) {
		AddToList(ae->name);
	}
}

void Archiver::ArchiveAll()
{
	QString fileName = QFileDialog::getSaveFileName(this, ("Archive Files"),
		"", ("Archive (*.lz *.uu *.lrz *.lzo *.lz4 *.gz *.bz2 *.lzma *.xz *.cpio *.shar *.tar *.tar.gz *.tar.grz *.tar.xz *.tar.lzo *.tar.lzma *.tar.lz *.tar.lrz *.tar.lz4 *.tar.Z *.iso *.zip *.ar *.xar *.7z)"));
	
	archive = new LibArchiveQt(fileName);

	archive->updateInputFiles(selected);
	archive->createArchive();
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
