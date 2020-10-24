#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileSystemModel>
#include <QLabel>
#include <QTreeView>

void MainWindow::addTree(QString string) {
    QTreeView *view = new QTreeView;
    QFileSystemModel* model = new QFileSystemModel;
    view->setModel(model);
    view->setRootIndex(model->setRootPath(string));
    for (int i = 1; i < model->columnCount(); i++)
        view->hideColumn(i);
    view->setHeaderHidden(false);
    ui->toolBox->addItem(view, string);
    view->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(view, &QTreeView::doubleClicked, this, &MainWindow::doubleClicked);
    connect(view, &QTreeView::customContextMenuRequested, this, &MainWindow::click);
}

void MainWindow::doubleClicked(const QModelIndex &index) {
    ui->toolBox->currentIndex();
    QFileSystemModel *model = new QFileSystemModel;
    QFileInfo check_file(model->filePath(index));
    if (check_file.exists() && check_file.isFile()) {
        addFileEdit(model->fileName(index),model->filePath(index));
//        qDebug() << model->filePath(index) << " " << model->fileName(index);
    }
    delete model;
//    model->filePath(index);
//    model->fileName(index);
// передать два пути Серёге
//    if (check_file.exists() && check_file.isFile())
//        qDebug() << model->filePath(index) << " " << model->fileName(index);
}

void MainWindow::click(const QPoint& point) {
    QPoint globalPos = qobject_cast<QTreeView *> (ui->toolBox->widget(ui->toolBox->currentIndex()))->mapToGlobal(point);
    QMenu myMenu;
    myMenu.addAction("create file", this, [this]() {
        QString string = QFileDialog::getSaveFileName(this, "Save file", "",
            "All files");
        QFile mfile(string);
        mfile.open(QIODevice::WriteOnly);
        mfile.close();
        qDebug() << "yes" << string;
    });
    myMenu.addAction("delete file", this, [this, point]() {
        QTreeView *treeView = qobject_cast<QTreeView *> (this->ui->toolBox->widget(this->ui->toolBox->currentIndex()));
        QFileSystemModel *model = new QFileSystemModel;
        QFileInfo check_file(model->filePath(treeView->indexAt(point)));
        if (check_file.isFile())
            QFile(model->filePath(treeView->indexAt(point))).remove();
//        qDebug() << "delete file" << model->filePath(treeView->indexAt(point));
        delete model;
    });
    myMenu.addAction("create directory", this, []() {
//        QDir().mkdir("MyFolder");
        QFileInfo check_file("/Users/dmushynska/Desktop/new");
        if (check_file.isDir()) {
            QDir dir;
            dir.setPath("/Users/dmushynska/Desktop/new");
            qDebug() << dir.path() << dir.dirName();
        }
        qDebug() << "yes";
    });
    myMenu.addAction("delete directory", this, [this, point]() {
        QTreeView *treeView = qobject_cast<QTreeView *> (this->ui->toolBox->widget(this->ui->toolBox->currentIndex()));
        QFileSystemModel *model = new QFileSystemModel;
        QFileInfo check_file(model->filePath(treeView->indexAt(point)));
        if (check_file.isDir())
            QDir(model->filePath(treeView->indexAt(point))).removeRecursively();
//        qDebug() << "delete dir" << model->filePath(treeView->indexAt(point));
        delete model;
    });
    myMenu.exec(globalPos);
//qDebug() << point;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTabBar *bar =  ui->tabWidget->tabBar();
    connect(bar, &QTabBar::tabCloseRequested, this, &MainWindow::closeFile);
    addTree(QDir::currentPath());
    connect(ui->actionadd_mkdir, &QAction::triggered, this, &MainWindow::add_mkdir);
    connect(ui->action_Cut, &QAction::triggered, this, [this](){
        for(int i = 0; i < this->ui->tabWidget->count(); i++) {
            if (qobject_cast<Editor*>(this->ui->tabWidget->widget(i))->getTextEdit()->isEnabled() && qobject_cast<Editor*>(this->ui->tabWidget->widget(i))->getTextEdit()->hasFocus())
                qobject_cast<Editor*>(this->ui->tabWidget->widget(i))->getTextEdit()->cut();
        }
    });
    connect(ui->action_Copy, &QAction::triggered, this, [this](){
        for(int i = 0; i < this->ui->tabWidget->count(); i++) {
            if (qobject_cast<Editor*>(this->ui->tabWidget->widget(i))->getTextEdit()->isEnabled() && qobject_cast<Editor*>(this->ui->tabWidget->widget(i))->getTextEdit()->hasFocus())
                qobject_cast<Editor*>(this->ui->tabWidget->widget(i))->getTextEdit()->copy();
        }
    });
    connect(ui->action_Undo, &QAction::triggered, this, [this](){
        for(int i = 0; i < this->ui->tabWidget->count(); i++) {
            if (qobject_cast<Editor*>(this->ui->tabWidget->widget(i))->getTextEdit()->isEnabled() && qobject_cast<Editor*>(this->ui->tabWidget->widget(i))->getTextEdit()->hasFocus())
                qobject_cast<Editor*>(this->ui->tabWidget->widget(i))->getTextEdit()->undo();
        }
    });
    connect(ui->action_Redo, &QAction::triggered, this, [this](){
        for(int i = 0; i < this->ui->tabWidget->count(); i++) {
            if (qobject_cast<Editor*>(this->ui->tabWidget->widget(i))->getTextEdit()->isEnabled() && qobject_cast<Editor*>(this->ui->tabWidget->widget(i))->getTextEdit()->hasFocus())
                qobject_cast<Editor*>(this->ui->tabWidget->widget(i))->getTextEdit()->redo();
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeFile(int index) {
ui->tabWidget->widget(index)->~QWidget();
}

void MainWindow::addFileEdit(const QString& name, const QString& fullPath) {
    Editor *newFile = new Editor;

    if (newFile->setValue(fullPath, ui)) {
        ui->tabWidget->addTab(newFile, name);
    }
    else {
         delete newFile;
    }
}


void MainWindow::on_action_Save_triggered()
{
//    addCursor = new QTextCursor(ui->textEdit->textCursor());
//    QTextCursor addCursor(ui->textEdit->textCursor());
//    addCursor->movePosition(QTextCursor::Down);
//    addCursor.insertText("Привет");
//    QFile file("/Users/solianovsk/Downloads/utext/utext/text");
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//        QMessageBox messageBox;
//        messageBox.critical(this,"Error","PErmision ERROR !");
//        messageBox.setFixedSize(500,200);
//    }
//    else {
//        file.write(ui->textEdit->toPlainText().toUtf8());
//        file.close();
//    }
}
