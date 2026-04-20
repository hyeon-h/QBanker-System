#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("QBankerSystem");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"송금";
}


void MainWindow::on_pushButton_2_clicked()
{
    qDebug()<<"입출금 내역";
}

void MainWindow::on_pushButton_3_clicked()
{
    qDebug()<<"회원 탈퇴";
}

