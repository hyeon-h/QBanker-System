#include "userwindow.h"
#include "ui_userwindow.h"

UserWindow::UserWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserWindow)
{
    ui->setupUi(this);
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::on_pushButton_clicked()
{
    qDebug()<<"송금";
}


void UserWindow::on_pushButton_2_clicked()
{
    qDebug()<<"입출금 내역";
}


void UserWindow::on_pushButton_3_clicked()
{
    qDebug()<<"회원 탈퇴";
}

