#include "userwindow.h"
#include "ui_userwindow.h"
#include "senddialog.h"
#include "userhistorywindow.h"
#include <QMessageBox>
UserWindow::UserWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    sendDialog = new SendDialog(this);
    userHistoryWindow = new UserHistoryWindow(this);
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::on_pushButton_clicked()
{
    qDebug()<<"송금";
    sendDialog->clearInputs();
    sendDialog->show();
    this->hide();
}


void UserWindow::on_pushButton_2_clicked()
{
    qDebug()<<"입출금 내역";
    userHistoryWindow->show();
    this->hide();
}


void UserWindow::on_pushButton_3_clicked()
{
    qDebug()<<"회원 탈퇴";
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "회원 탈퇴",
                                  "정말로 탈퇴하시겠습니까?",
                                  QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes)
    {
        // 탈퇴 처리
    }
}

