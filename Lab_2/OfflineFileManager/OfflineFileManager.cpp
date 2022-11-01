#include "OfflineFileManager.h"
#include <QCommandLineParser>
#include <QFileIconProvider>
#include <QFileSystemModel>
#include <QDesktopServices>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QFileDialog>
#include <QScreen>
#include <Qscroller>
#include <QStringList>
#include <QVBoxLayout>
#include <QPushButton>
#include <QThread>
#include <QUrl>
#include <QMenu>

#include "PropertiesWindow.h"
#include "PropertiesLogic.h"

const QString savingFile = "static.fsh";


OfflineFileManager::OfflineFileManager(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    model = new QFileInfoModel();
    
    try {
        model->readFile(savingFile);
    }
    catch (const std::exception &e) {
        QMessageBox::warning(this, tr("Offline File Manager"),
            tr(e.what()), QMessageBox::Close);
    };

    treeViewInit(ui.fileSystemTree, model);

    connect(ui.actionClose, &QAction::triggered, this, &OfflineFileManager::close);
    connect(ui.updateButton, &QToolButton::clicked, this, &OfflineFileManager::on_updateButton_clicked);
    connect(ui.upButton, &QToolButton::triggered, this, &OfflineFileManager::on_upButton_clicked);
    connect(ui.homeButton, &QToolButton::clicked, this, &OfflineFileManager::on_homeButton_clicked);
    connect(ui.actionSave, &QAction::triggered, this, &OfflineFileManager::on_saveAction_triggered);
    connect(ui.actionOpen, &QAction::triggered, this, &OfflineFileManager::on_openAction_triggered);
    connect(ui.fileSystemTree, &QTreeView::doubleClicked, model, &QFileInfoModel::fetchMore);
    connect(ui.addressLine, &QLineEdit::editingFinished, this, &OfflineFileManager::on_editLine_editingFinished);
}

OfflineFileManager::~OfflineFileManager()
{
    model->writeFile(savingFile, maxDepth);
    delete model;
}

void OfflineFileManager::on_treeWidget_clicked(QModelIndex index)
{
    QList<QString> path = model->getPath(index);
    QString spath;
    foreach(auto file, path) { 
        file.removeIf([](QChar c) {return c == QChar('/') || c == QChar('\\'); });
        spath += '/' + file; 
    }

    ui.addressLine->blockSignals(true);
    ui.addressLine->setText(spath);
    ui.addressLine->blockSignals(false);
}

void OfflineFileManager::action_openInFileExplorer()
{
    QModelIndex index = ui.fileSystemTree->currentIndex();

    QList<QString> path = model->getPath(index); path.removeLast();
    QString spath;
    foreach(auto file, path) spath += '/' + file;
    spath.remove(0, 1);

    if (path.isEmpty())
        QDesktopServices::openUrl(QUrl::fromLocalFile(""));
    else
    if (!QDesktopServices::openUrl(QUrl::fromLocalFile(spath)))
        QMessageBox::critical(this, tr("Offline File Manager"),
            tr("No access"), QMessageBox::Close);
}

void OfflineFileManager::action_openFile()
{
    QModelIndex index = ui.fileSystemTree->currentIndex();

    QList<QString> path = model->getPath(index);
    QString spath;
    foreach(auto file, path) spath += '/' + file;
    spath.remove(0, 1);

    if (!QDesktopServices::openUrl(QUrl::fromLocalFile(spath)))
        QMessageBox::critical(this, tr("Offline File Manager"),
            tr("No access"), QMessageBox::Close);
}

void OfflineFileManager::action_Properties()
{
    QModelIndex index = ui.fileSystemTree->currentIndex();
    PropertiesLogic* properties = new PropertiesLogic(index, model);

    QDialog* widget = new QDialog(this);
    QVBoxLayout* layout = new QVBoxLayout(widget);
    PropertiesWindow* properties_window = new PropertiesWindow(widget);
    widget->setWindowTitle("Properties");
    QPushButton* buttonOk = new QPushButton(widget);
    QPushButton* buttonCancel = new QPushButton(widget);
    QPushButton* buttonSave = new QPushButton(widget);
    buttonCancel->setText("Cancel");
    buttonOk->setText("OK");
    buttonSave->setText("Save");
    connect(buttonCancel, &QPushButton::clicked, widget, &QWidget::close);
    connect(buttonOk, &QPushButton::clicked, widget, &QWidget::close);
    connect(buttonOk, &QPushButton::clicked, properties_window, &PropertiesWindow::saveTextSlot);
    connect(buttonSave, &QPushButton::clicked, properties_window, &PropertiesWindow::saveTextSlot);
    connect(properties_window, &PropertiesWindow::saveTextSignal, this, &OfflineFileManager::saveMeta);

    properties_window->setFixedHeight(this->height() / 1.6);
    properties_window->setFixedWidth(this->width() / 2);
    properties_window->setColumnCount(2);
    properties_window->setRowCount(10);
    properties_window->setColumnWidth(0, 2 * properties_window->width() / 6);
    properties_window->setColumnWidth(1, 3 * properties_window->width() / 5);

    for (size_t i = 0; i < properties_window->rowCount(); i++)
        properties_window->setRowHeight(i, properties_window->height() / 70);

    properties_window->setRowHeight((int)ColunmsOrder::CUSTOM_METHADATA, properties_window->height() / 8);
    properties_window->setAttribute(Qt::WA_DeleteOnClose);
    this->setCursor(QCursor(Qt::ArrowCursor));

    properties_window->setItem((int)ColunmsOrder::NAME, 0, new QTableWidgetItem("Name:"));
    properties_window->setItem((int)ColunmsOrder::NAME, 1, new QTableWidgetItem(properties->getName()));

    properties_window->setItem((int)ColunmsOrder::TYPE, 0, new QTableWidgetItem("Type:"));
    properties_window->setItem((int)ColunmsOrder::TYPE, 1, new QTableWidgetItem(properties->getType()));

    properties_window->setItem((int)ColunmsOrder::SIZE, 0, new QTableWidgetItem("Size:"));
    properties_window->setItem((int)ColunmsOrder::SIZE, 1, new QTableWidgetItem(properties->getSize()));

    properties_window->setItem((int)ColunmsOrder::ICON_NAME, 0, new QTableWidgetItem("Icon name:"));
    properties_window->setItem((int)ColunmsOrder::ICON_NAME, 1, new QTableWidgetItem(properties->getIconName()));

    properties_window->setItem((int)ColunmsOrder::GROUP, 0, new QTableWidgetItem("Group:"));
    properties_window->setItem((int)ColunmsOrder::GROUP, 1, new QTableWidgetItem(properties->getGroup()));

    properties_window->setItem((int)ColunmsOrder::OWNER, 0, new QTableWidgetItem("Owner:"));
    properties_window->setItem((int)ColunmsOrder::OWNER, 1, new QTableWidgetItem(properties->getOwner()));

    properties_window->setItem((int)ColunmsOrder::OWNER_ID, 0, new QTableWidgetItem("Owner ID:"));
    properties_window->setItem((int)ColunmsOrder::OWNER_ID, 1, new QTableWidgetItem(properties->getOwnerid()));

    properties_window->setItem((int)ColunmsOrder::DATE_CREATED, 0, new QTableWidgetItem("Date created:"));
    properties_window->setItem((int)ColunmsOrder::DATE_CREATED, 1, new QTableWidgetItem(properties->getCreated()));

    properties_window->setItem((int)ColunmsOrder::DATE_MODIDFIED, 0, new QTableWidgetItem("Date modified:"));
    properties_window->setItem((int)ColunmsOrder::DATE_MODIDFIED, 1, new QTableWidgetItem(properties->getLastModified()));

    properties_window->setItem((int)ColunmsOrder::CUSTOM_METHADATA, 0, new QTableWidgetItem("Custom metadata:"));
    properties_window->setItem((int)ColunmsOrder::CUSTOM_METHADATA, 1, new QTableWidgetItem(properties->getCustomMethadata()));

    properties_window->setHorizontalHeaderItem(0, new QTableWidgetItem("Property"));
    properties_window->setHorizontalHeaderItem(1, new QTableWidgetItem("Value"));
    properties_window->verticalHeader()->hide();


    QTableWidgetItem* customItem = properties_window->item(properties_window->rowCount() - 1, 
                                                            properties_window->columnCount() - 1);
    Qt::ItemFlags writeFlag = customItem->flags();

    // Make readonly
    for (size_t i = 0; i < properties_window->rowCount(); ++i)
        for (size_t j = 0; j < properties_window->columnCount(); ++j) {
            QTableWidgetItem* item = properties_window->item(i, j);
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        }

    // Set custom meta editable
    customItem->setFlags(writeFlag);

    layout->addWidget(properties_window, 0);
    layout->addWidget(buttonCancel);
    layout->addWidget(buttonSave);
    layout->addWidget(buttonOk);
    widget->setLayout(layout);
    widget->exec();

    delete properties_window;
    delete properties;
    delete widget;
}

void OfflineFileManager::on_customContextMenu(const QPoint& point)
{
    QPoint globalPos = ui.fileSystemTree->mapToGlobal(point);

    QMenu menu(this);
    menu.addAction("Open",
        this, &OfflineFileManager::action_openFile);
    menu.addAction("Open in file explorer",
        this, &OfflineFileManager::action_openInFileExplorer);
    menu.addAction("Properties",
        this, &OfflineFileManager::action_Properties);

    menu.exec(globalPos);
}

void OfflineFileManager::on_updateButton_clicked()
{
    switch (regime)
    {
    case OfflineFileManager::FILESYSTEM:
    {
        treeViewInit(ui.fileSystemTree, new QFileSystemModel);

        this->model->genStaticSystemModel(maxDepth);
        treeViewInit(ui.fileSystemTree, model);
        break;
    }
    case OfflineFileManager::EXTERNAL_DRIVES:
    {
        this->model->genExternalDrivesModel(maxDepth);
        // treeViewInit(ui.fileSystemTree, model->readFile("tmp.bin"));
        treeViewInit(ui.fileSystemTree, model);
        break;
    }
    default:
        break;
    }
}

void OfflineFileManager::on_saveAction_triggered() 
{
    QString fileName = QFileDialog::getSaveFileName(this, 
        ("Save File"),"", ("File system hierarchy (*.fsh)"));

    try {
        model->writeFile(fileName, maxDepth);
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, tr("Offline File Manager"),
            tr(e.what()), QMessageBox::Close);
    }
}

void OfflineFileManager::on_openAction_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, ("Open File"),
        "", ("File system hierarchy (*.fsh)"));
    
    try {
        model->readFile(fileName);
    }
    catch(const std::exception &e) {
        QMessageBox::critical(this, tr("Offline File Manager"),
            tr(e.what()), QMessageBox::Close);
    }
    treeViewInit(ui.fileSystemTree, model);
}

void OfflineFileManager::on_homeButton_clicked()
{
    ui.addressLine->setText("");
    ui.fileSystemTree->setCurrentIndex(QModelIndex());
    ui.fileSystemTree->collapseAll();
}

void OfflineFileManager::on_editLine_editingFinished()
{
    QString path = ui.addressLine->text();
    QModelIndex index = model->byPath(path);
    
    if (index.isValid()) {
        ui.fileSystemTree->expand(index);
        ui.fileSystemTree->setCurrentIndex(index);
    }
}

void OfflineFileManager::on_upButton_clicked()
{
    QString path = ui.addressLine->text();
    QModelIndex index = model->byPath(path);
    
    ui.fileSystemTree->collapseAll();
    ui.fileSystemTree->setCurrentIndex(index.parent());

    QStringList newPath = model->getPath(index.parent());
    QString spath;
    foreach(auto file, newPath) { 
        file.removeIf([](QChar c) {return c == QChar('/') || c == QChar('\\'); });
        spath += '/' + file; };

    ui.addressLine->blockSignals(true);
    ui.addressLine->setText(spath);
    ui.addressLine->blockSignals(false);
}

void OfflineFileManager::saveMeta(const QString& str)
{
    QModelIndex index = ui.fileSystemTree->currentIndex();
    index = index.siblingAtColumn((int)ColunmsOrder::CUSTOM_METHADATA);
    QStandardItem* item = model->itemFromIndex(index);
    item->setData(str, 0);
}

void OfflineFileManager::treeViewInit(QTreeView* tree, QAbstractItemModel* model)
{
    tree->setModel(model);

    for (size_t i = 4; i < tree->model()->columnCount(); i++)
        tree->hideColumn(i); // only 4 columns need to be displayed

    tree->setAnimated(false);
    tree->setIndentation(20);
    tree->setSortingEnabled(true);
    const QSize availableSize = tree->screen()->availableGeometry().size();
    tree->setColumnWidth(0, tree->width() / 2);
    QScroller::grabGesture(tree, QScroller::TouchGesture);
    ui.fileSystemTree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.fileSystemTree->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui.fileSystemTree, &QTreeView::activated, this, &OfflineFileManager::on_treeWidget_clicked);
    connect(ui.fileSystemTree, &QTreeView::customContextMenuRequested, this, &OfflineFileManager::on_customContextMenu);
    connect(tree, &QTreeView::clicked, this, &OfflineFileManager::on_treeWidget_clicked);
}
