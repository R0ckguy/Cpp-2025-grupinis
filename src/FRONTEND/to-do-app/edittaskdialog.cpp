#include "edittaskdialog.h"
#include "ui_edittaskdialog.h"

EditTaskDialog::EditTaskDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditTaskDialog)
{
    ui->setupUi(this);
    setWindowTitle("Edit task");
    ui->dueDateEdit->setDateTime(QDateTime::currentDateTime());
    ui->errorLabel->setStyleSheet("color: red;");
    ui->errorLabel->clear();
    setModal(true);
    resize(400, 300);

    connect(ui->saveBtn, &QPushButton::clicked, this, &EditTaskDialog::on_saveBtn_clicked);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &EditTaskDialog::on_cancelBtn_clicked);
    // TODO: add window icon
}

EditTaskDialog::~EditTaskDialog()
{
    delete ui;
}

QString EditTaskDialog::getTitle() const
{
    return ui->titleEdit->text();
}

QString EditTaskDialog::getDescription() const
{
    return ui->descriptionEdit->toPlainText();
}

QDateTime EditTaskDialog::getDueDate() const
{
    return ui->dueDateEdit->dateTime();
}

void EditTaskDialog::setTaskData(const QString &title, const QString &description, const QDateTime &dueDate)
{
    ui->titleEdit->setText(title);
    ui->descriptionEdit->setPlainText(description);
    ui->dueDateEdit->setDateTime(dueDate);
    ui->errorLabel->clear();
}



void EditTaskDialog::on_saveBtn_clicked()
{
    // Validate input
    if (ui->titleEdit->text().isEmpty() || ui->descriptionEdit->toPlainText().isEmpty()) {
        ui->errorLabel->setText("Please enter both title and description.");
        return;
    }

    // Clear error and accept the dialog
    ui->errorLabel->clear();
    accept(); // This closes the dialog with QDialog::Accepted result
}


void EditTaskDialog::on_cancelBtn_clicked()
{
    reject();
}

