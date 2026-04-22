#include "userwindow.h"
#include "ui_userwindow.h"
#include "senddialog.h"
#include "userhistorywindow.h"
#include <QMessageBox>
#include "history.h"
#include "datamanager.h"

UserWindow::UserWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserWindow)
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
    sendDialog = new SendDialog(this);
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
        History h;
        h.dateTime = QDateTime::currentDateTime();
        h.from = DataManager::instance().loginId;
        h.to = "";
        h.action = ActionType::Delete;
        h.amount = 0;

        DataManager::instance().addHistory(h);

        this->close();
    }
}

