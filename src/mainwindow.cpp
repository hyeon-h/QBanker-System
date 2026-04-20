#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userwindow.h"
#include "adminwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("QBankerSystem");
    userWin = new UserWindow(this);
    adminWin = new AdminWindow(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"USER LOGIN OK";
    userWin->show();
    this->hide();
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug()<<"ADMIN LOGIN OK";
    adminWin->show();
    this->hide();
}


