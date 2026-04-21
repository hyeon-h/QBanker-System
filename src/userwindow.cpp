#include "userwindow.h"
#include "ui_userwindow.h"
#include "senddialog.h"
#include "userhistorywindow.h"
#include <QMessageBox>
UserWindow::UserWindow(QWidget *parent , QString id)
    : QMainWindow(parent)
    , ui(new Ui::UserWindow)
    , loginId(id)
{
    ui->setupUi(this);
    setWindowTitle("UserLogin");
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::on_pushButton_clicked()
{
    qDebug()<<"송금";
    qDebug()<<loginId;
    sendDialog = new SendDialog(this, loginId);
    sendDialog->setAttribute(Qt::WA_DeleteOnClose);
    sendDialog->clearInputs();
    sendDialog->show();
}


void UserWindow::on_pushButton_2_clicked()
{
    qDebug()<<"입출금 내역";
    userHistoryWindow = new UserHistoryWindow(this);
    userHistoryWindow->setAttribute(Qt::WA_DeleteOnClose);
    userHistoryWindow->show();
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

