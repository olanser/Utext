#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCursor>
#include <QTextEdit>
#include <QTabBar>
#include <QFileDialog>
#include "editor.h"
#include<QtDebug>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void click(const QModelIndex &index);
    void clickMouse(const QPoint& index);
    void addTree(QString string);
    void addFileEdit(const QString& name, const QString& fullPath);
    void closeFile(int index);
    void windowFind(const QString& text, bool isRegex, QTextDocument::FindFlags flags);
    void windowReplace(const QString& textFind, const QString& textReplace, bool isRegex, QTextDocument::FindFlags flags);
    void add_mkdir() {
        QString string = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home",
                                                           QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if (string.count() != 0) {
            addTree(string);
        }
    }
//    void test() {
//        qDebug() << "yes;";
//    }

private slots:
    void on_action_Save_triggered();

    void on_action_Find_triggered();

private:
    Ui::MainWindow *ui;
    QTextCursor *addCursor;
    bool isDark = true;
};

#endif // MAINWINDOW_H
