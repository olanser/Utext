#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QFile>
#include <QMessageBox>
#include <QTextEdit>
namespace Ui {
class Editor;
}

namespace Ui {
class MainWindow;
}

class Editor : public QWidget
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);
    bool setValue(const QString& newFullPath, Ui::MainWindow *mui);
    const QString& getFullPath(void);
    ~Editor();
    QTextEdit *getTextEdit();
private:
    Ui::Editor *ui;
    QString fullPath;
};
#endif // EDITOR_H
