#include "mainwindow.h"
#include "./ui_mainwindow.h"
//#include "../../BACKEND/TaskManager.h"
#include <QCheckBox>
#include <QHBoxLayout>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupTable();
    setWindowTitle("To-do app");
    resize(800, 500);
    // TODO: add loading tasks from .json file
    // TODO: add window icon
}

MainWindow::~MainWindow()
{
    // TODO: add saving tasks to .json file
    delete ui;
}

void MainWindow::setupTable() {
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels({"✔", "Title", "Description", "Due Date", "Actions"});
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    for (int col = 1; col < ui->tableWidget->columnCount(); ++col) {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(col, QHeaderView::Stretch);
    }
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::addTask(const QString &title, const QString &description, const QDateTime &dueDate)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    // Checkbox
    QCheckBox* check = new QCheckBox();
    connect(check, &QCheckBox::checkStateChanged, this, &MainWindow::toggleComplete);
    ui->tableWidget->setCellWidget(row, 0, check);

    // Title
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(title));

    // Description
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(description));

    // Due date
    QString dueDateStr = dueDate.toString("yyyy-MM-dd HH:mm");
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(dueDateStr));

    // Actions (Edit and Delete)
    QWidget* actionWidget = new QWidget();
    QPushButton* editBtn = new QPushButton("Edit");
    QPushButton* deleteBtn = new QPushButton("Delete");

    connect(editBtn, &QPushButton::clicked, this, &MainWindow::editTask);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::deleteConfirm);

    QHBoxLayout* layout = new QHBoxLayout(actionWidget);
    layout->addWidget(editBtn);
    layout->addWidget(deleteBtn);
    layout->setContentsMargins(2, 2, 2, 2);
    layout->setSpacing(4);
    layout->setAlignment(Qt::AlignCenter);
    actionWidget->setLayout(layout);

    ui->tableWidget->setCellWidget(row, 4, actionWidget);
}

void MainWindow::on_addTaskBtn_clicked()
{
    AddTaskDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        addTask(dialog.getTitle(), dialog.getDescription(), dialog.getDueDate());
    }
}

void MainWindow::deleteTask()
{
    QPushButton* senderBtn = qobject_cast<QPushButton*>(sender());
    if (!senderBtn) return;

    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        QWidget* widget = ui->tableWidget->cellWidget(i, 4);
        if (widget) {
            QList<QPushButton*> buttons = widget->findChildren<QPushButton*>();
            if (buttons.contains(senderBtn)) {
                ui->tableWidget->removeRow(i);
                // TODO: add removing task from .json file with TaskManager
                break;
            }
        }
    }
}

void MainWindow::toggleComplete(int state)
{
    QCheckBox* senderCheckbox = qobject_cast<QCheckBox*>(sender());
    if (!senderCheckbox) return;

    bool checked = (state == Qt::Checked);

    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        QWidget* widget = ui->tableWidget->cellWidget(i, 0);
        if (widget == senderCheckbox) {
            for (int col = 1; col <= 3; ++col) {
                QTableWidgetItem* item = ui->tableWidget->item(i, col);
                if (item) {
                    if (checked) {
                        item->setForeground(QColor(100, 100, 100));
                        item->setBackground(QColor(240, 240, 240));
                        QFont font = item->font();
                        font.setStrikeOut(true);
                        item->setFont(font);
                    } else {
                        item->setForeground(Qt::black);
                        item->setBackground(Qt::white);
                        QFont font = item->font();
                        font.setStrikeOut(false);
                        item->setFont(font);
                    }
                }
            }
            if (checked) {
                ui->tableWidget->item(i, 0) ?
                    ui->tableWidget->item(i, 0)->setBackground(QColor(240, 240, 240)) : void();
                QWidget* actionsWidget = ui->tableWidget->cellWidget(i, 4);
                if (actionsWidget) {
                    actionsWidget->setStyleSheet("background-color: rgb(240, 240, 240);");
                }
            } else {
                ui->tableWidget->item(i, 0) ?
                    ui->tableWidget->item(i, 0)->setBackground(Qt::white) : void();
                QWidget* actionsWidget = ui->tableWidget->cellWidget(i, 4);
                if (actionsWidget) {
                    actionsWidget->setStyleSheet("");
                }
            }
            break;
        }
    }
}

void MainWindow::editTask()
{
    QPushButton* senderBtn = qobject_cast<QPushButton*>(sender());
    if (!senderBtn) return;

    // Find which row contains the clicked edit button
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        QWidget* widget = ui->tableWidget->cellWidget(i, 4);
        if (widget) {
            // Find all buttons in the actions widget
            QList<QPushButton*> buttons = widget->findChildren<QPushButton*>();
            if (buttons.contains(senderBtn)) {
                // Get current values from the row
                QTableWidgetItem* titleItem = ui->tableWidget->item(i, 1);
                QTableWidgetItem* descItem = ui->tableWidget->item(i, 2);
                QTableWidgetItem* dateItem = ui->tableWidget->item(i, 3);

                if (titleItem && descItem && dateItem) {
                    // Parse the date string
                    QDateTime dateTime = QDateTime::fromString(dateItem->text(), "yyyy-MM-dd HH:mm");
                    if (!dateTime.isValid()) {
                        dateTime = QDateTime::currentDateTime();
                    }

                    // Create and show the edit dialog
                    EditTaskDialog dialog(this);
                    dialog.setTaskData(titleItem->text(), descItem->text(), dateTime);

                    if (dialog.exec() == QDialog::Accepted) {
                        // User clicked Save - update the row with new data
                        titleItem->setText(dialog.getTitle());
                        descItem->setText(dialog.getDescription());
                        QString newDateStr = dialog.getDueDate().toString("yyyy-MM-dd HH:mm");
                        dateItem->setText(newDateStr);

                        // Get checkbox state to maintain completed/uncompleted styling
                        QCheckBox* checkbox = qobject_cast<QCheckBox*>(ui->tableWidget->cellWidget(i, 0));
                        if (checkbox && checkbox->isChecked()) {
                            // Reapply completed task styling
                            for (int col = 1; col <= 3; ++col) {
                                QTableWidgetItem* item = ui->tableWidget->item(i, col);
                                if (item) {
                                    item->setForeground(QColor(100, 100, 100));
                                    item->setBackground(QColor(240, 240, 240));
                                    QFont font = item->font();
                                    font.setStrikeOut(true);
                                    item->setFont(font);
                                }
                            }
                        }
                    }
                    // If user clicked Cancel, dialog closes and nothing changes
                }
                break;
            }
        }
    }
}

void MainWindow::deleteConfirm() {
    QPushButton* senderBtn = qobject_cast<QPushButton*>(sender());
    if (!senderBtn) return;

    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        QWidget* widget = ui->tableWidget->cellWidget(i, 4);
        if (widget) {
            // Find all buttons in the actions widget
            QList<QPushButton*> buttons = widget->findChildren<QPushButton*>();
            if (buttons.contains(senderBtn)) {
                // Get current values from the row
                QTableWidgetItem* titleItem = ui->tableWidget->item(i, 1);
                QTableWidgetItem* descItem = ui->tableWidget->item(i, 2);
                QTableWidgetItem* dateItem = ui->tableWidget->item(i, 3);

                if (titleItem && descItem && dateItem) {
                    // Parse the date string
                    QDateTime dateTime = QDateTime::fromString(dateItem->text(), "yyyy-MM-dd HH:mm");
                    if (!dateTime.isValid()) {
                        dateTime = QDateTime::currentDateTime();
                    }

                    // Create and show the edit dialog
                    deleteConfirmDialog dialog(this);

                    if (dialog.exec() == QDialog::Accepted) {
                        ui->tableWidget->removeRow(i);
                        // TODO: add removing task from .json file with TaskManager
                    }
                    // If user clicked Cancel, dialog closes and nothing changes
                }
                break;
            }
        }
    }


}
