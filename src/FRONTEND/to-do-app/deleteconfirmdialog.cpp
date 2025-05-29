#include "deleteconfirmdialog.h"
#include "ui_deleteconfirmdialog.h"

deleteConfirmDialog::deleteConfirmDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::deleteConfirmDialog)
{
    ui->setupUi(this);
    setWindowTitle("Delete task");
}

deleteConfirmDialog::~deleteConfirmDialog()
{
    delete ui;
}

void deleteConfirmDialog::on_buttonBox_accepted()
{
    accept();
}


void deleteConfirmDialog::on_buttonBox_rejected()
{
    reject();
}

