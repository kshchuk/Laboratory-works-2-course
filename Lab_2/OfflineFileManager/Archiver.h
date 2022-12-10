#pragma once

#include <QMainWindow>
#include <QFileIconProvider>

#include "ui_Archiver.h"

//#include "archiever/libarchiveqt.h"


class Archiver : public QMainWindow
{
	Q_OBJECT

public:
	Archiver(QWidget *parent = nullptr);
	~Archiver();

private slots:
	void SelectFiles();
	void SelectArchive();
	void ClearAll();
	void AddToList(QString path);
	void ArchiveAll();
	//void ArchiveSelected();
	void UnarchiveAll();
	//void UnarchiveSelected();

private:
	Ui::ArchiverClass ui;
	QStringList selected; // paths
	QStringList listSelected;
	QFileIconProvider icons;
	//LibArchiveQt* archive;

	void UpdateSelected();
};
