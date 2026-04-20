#include "userhistorywindow.h"
#include "ui_userhistorywindow.h"

UserHistoryWindow::UserHistoryWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserHistoryWindow)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate(QDate::currentDate().year(),1,1));
    ui->dateEdit_2->setDate(QDate::currentDate());
}

UserHistoryWindow::~UserHistoryWindow()
{
    delete ui;
}

void UserHistoryWindow::on_pushButton_clicked()
{
    qDebug()<<"ok";
}

void UserHistoryWindow::on_pushButton_2_clicked()
{
    qDebug()<<"cancel";
    this->close();
}

void UserHistoryWindow::closeEvent(QCloseEvent *event)
{
    parentWidget()->show();
    event->accept();
}
