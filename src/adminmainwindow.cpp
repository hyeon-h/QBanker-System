#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"

AdminMainWindow::AdminMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminMainWindow)
{
    ui->setupUi(this);
}

AdminMainWindow::~AdminMainWindow()
{
    delete ui;
}

void AdminMainWindow::on_pushButton_clicked()
{
    qDebug()<<"가입자 조회";
}


void AdminMainWindow::on_pushButton_2_clicked()
{
    qDebug()<<"입출금 내역";
}

