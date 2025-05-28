#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "edittaskdialog.h"
#include "deleteconfirmdialog.h"
#include "addtaskdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_addTaskBtn_clicked();
    void deleteTask();
    void toggleComplete(int state);
    void editTask();
    void deleteConfirm();
    void addTask(const QString &title, const QString &description, const QDateTime &dueDate);

private:
    Ui::MainWindow *ui;
    void setupTable();
};
#endif // MAINWINDOW_H
