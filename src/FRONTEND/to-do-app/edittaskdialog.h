#ifndef EDITTASKDIALOG_H
#define EDITTASKDIALOG_H

#include <QDialog>

namespace Ui {
class EditTaskDialog;
}

class EditTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditTaskDialog(QWidget *parent = nullptr);
    ~EditTaskDialog();
    void setTaskData(const QString &title, const QString &description, const QDateTime &dueDate);

    QString getTitle() const;
    QString getDescription() const;
    QDateTime getDueDate() const;

private slots:
    void on_saveBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::EditTaskDialog *ui;
};

#endif // EDITTASKDIALOG_H
