#include "usermainwindow.h"
#include "ui_usermainwindow.h"

UserMainWindow::UserMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);
}

UserMainWindow::~UserMainWindow()
{
    delete ui;
}

void UserMainWindow::on_pushButton_clicked()
{
    qDebug()<<"송금";
}


void UserMainWindow::on_pushButton_2_clicked()
{
    qDebug()<<"입출금 내역";
}


void UserMainWindow::on_pushButton_3_clicked()
{
    qDebug()<<"회원 탈퇴";
}

