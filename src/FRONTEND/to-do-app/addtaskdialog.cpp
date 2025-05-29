#include "addtaskdialog.h"
#include "ui_addtaskdialog.h"

AddTaskDialog::AddTaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTaskDialog)
    
{
    ui->setupUi(this);
    setWindowTitle("Add task");
    ui->errorLabel->setStyleSheet("color: red;");
    ui->errorLabel->clear();
    setModal(true);
    resize(400, 300);
    ui->dueDateEdit->setDateTime(QDateTime::currentDateTime());
    connect(ui->saveBtn, &QPushButton::clicked, this, &AddTaskDialog::on_saveBtn_clicked);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &AddTaskDialog::on_cancelBtn_clicked);
}

AddTaskDialog::~AddTaskDialog()
{
    delete ui;
}

QString AddTaskDialog::getTitle() const {
    return ui->titleEdit->text();
}

QString AddTaskDialog::getDescription() const {
    return ui->descriptionEdit->toPlainText();
}

QDateTime AddTaskDialog::getDueDate() const {
    return ui->dueDateEdit->dateTime();
}

void AddTaskDialog::on_cancelBtn_clicked()
{
    reject();
}


void AddTaskDialog::on_saveBtn_clicked()
{
    if (ui->titleEdit->text().isEmpty() || ui->descriptionEdit->toPlainText().isEmpty()) {
        ui->errorLabel->setText("Please enter both title and description.");
        return;
    }

    emit taskDataEntered(
        ui->titleEdit->text(),
        ui->descriptionEdit->toPlainText(),
        ui->dueDateEdit->dateTime()
    );

    accept();
}

