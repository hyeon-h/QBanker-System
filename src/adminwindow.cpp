#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    adminHistoryWindow = new AdminHistoryWindow(this);
    memInfoDialog = new MemInfoDialog(this);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_pushButton_clicked()
{
    qDebug()<<"가입자 조회";
    memInfoDialog->show();
    this->hide();
}


void AdminWindow::on_pushButton_2_clicked()
{
    qDebug()<<"입출금 내역";
    adminHistoryWindow->show();
    this->hide();
}