#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QCheckBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupTable();
    ui->dueDateEdit->setDateTime(QDateTime::currentDateTime());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupTable() {
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels({"✔", "Title", "Description", "Due Date", "Actions"});
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);  // checkbox column
    for (int col = 1; col < ui->tableWidget->columnCount(); ++col) {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(col, QHeaderView::Stretch);
    }
}

void MainWindow::on_addTaskBtn_clicked()
{
    QString title = ui->titleEdit->text();
    QString description = ui->descriptionEdit->toPlainText();
    QDateTime dueDate = ui->dueDateEdit->dateTime();
    QString date = dueDate.toString("yyyy-MM-dd HH:mm");

    int newRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(newRow);

    QCheckBox* check = new QCheckBox();
    ui->tableWidget->setCellWidget(newRow, 0, check);

    ui->tableWidget->setItem(newRow, 1, new QTableWidgetItem(title));
    ui->tableWidget->setItem(newRow, 2, new QTableWidgetItem(description));
    ui->tableWidget->setItem(newRow, 3, new QTableWidgetItem(date));

    // Clear inputs
    ui->titleEdit->clear();
    ui->descriptionEdit->clear();
}

