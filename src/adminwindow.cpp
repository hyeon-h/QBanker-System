#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    setWindowTitle("AdminLogin");
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_pushButton_clicked()
{
    qDebug()<<"가입자 조회";
    memInfoDialog = new MemInfoDialog(this);
    memInfoDialog->setAttribute(Qt::WA_DeleteOnClose);
    memInfoDialog->show();
}

void AdminWindow::on_pushButton_2_clicked()
{
    qDebug()<<"입출금 내역";
    adminHistoryWindow = new AdminHistoryWindow(this);
    adminHistoryWindow->setAttribute(Qt::WA_DeleteOnClose);
    adminHistoryWindow->show();
}