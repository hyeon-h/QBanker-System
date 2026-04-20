#include "adminhistorywindow.h"
#include "ui_adminhistorywindow.h"

AdminHistoryWindow::AdminHistoryWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminHistoryWindow)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate(QDate::currentDate().year(),1,1));
    ui->dateEdit_2->setDate(QDate::currentDate());
}

AdminHistoryWindow::~AdminHistoryWindow()
{
    delete ui;
}

void AdminHistoryWindow::on_pushButton_clicked()
{
    qDebug()<<"Ok";
}


void AdminHistoryWindow::on_pushButton_2_clicked()
{
    qDebug()<<"Cancel";
    this->close();
}

void AdminHistoryWindow::closeEvent(QCloseEvent *event)
{
    parentWidget()->show();
    event->accept();
}