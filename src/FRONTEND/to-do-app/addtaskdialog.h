#ifndef ADDTASKDIALOG_H
#define ADDTASKDIALOG_H

#include <QDialog>

namespace Ui {
class AddTaskDialog;
}

class AddTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTaskDialog(QWidget *parent = nullptr);
    ~AddTaskDialog();
    QString getTitle() const;
    QString getDescription() const;
    QDateTime getDueDate() const;

private slots:
    void on_cancelBtn_clicked();
    void on_saveBtn_clicked();

private:
    Ui::AddTaskDialog *ui;

signals:
    void taskDataEntered(const QString &title, const QString &description, const QDateTime &dueDate);

};

#endif // ADDTASKDIALOG_H
