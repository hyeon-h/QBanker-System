#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "usermainwindow.h"
#include "adminmainwindow.h"

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
    qDebug()<<"USER LOGIN OK";
    UserMainWindow* userWin = new UserMainWindow();
    userWin->setAttribute(Qt::WA_DeleteOnClose);
    userWin->show();
    this->hide();
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug()<<"ADMIN LOGIN OK";
    AdminMainWindow* adminWin = new AdminMainWindow();
    adminWin->setAttribute(Qt::WA_DeleteOnClose);
    adminWin->show();
    this->hide();
}


