#ifndef DELETECONFIRMDIALOG_H
#define DELETECONFIRMDIALOG_H

#include <QDialog>

namespace Ui {
class deleteConfirmDialog;
}

class deleteConfirmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit deleteConfirmDialog(QWidget *parent = nullptr);
    ~deleteConfirmDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::deleteConfirmDialog *ui;
};

#endif // DELETECONFIRMDIALOG_H
