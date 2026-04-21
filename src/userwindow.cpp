#include "userwindow.h"
#include "ui_userwindow.h"
#include "senddialog.h"
#include "userhistorywindow.h"
#include <QMessageBox>
#include <QFile>
#include <QDomDocument>

UserWindow::UserWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    setWindowTitle("UserLogin");
    sendDialog = new SendDialog(this);
    userHistoryWindow = new UserHistoryWindow(this);
}

UserWindow::~UserWindow()
{
    delete ui;
}
// UserWindow.cpp에 추가
#include <QFile>
#include <QDomDocument>

void UserWindow::refreshUserInfo()
{
    QString currentName = ui->label_2->text(); // 현재 라벨에 적힌 내 이름

    QFile file("../../data/user_data.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QDomDocument doc;
    doc.setContent(&file);
    file.close();

    QDomNodeList users = doc.elementsByTagName("User");
    for (int i = 0; i < users.count(); ++i) {
        QDomElement user = users.at(i).toElement();
        if (user.firstChildElement("Name").text() == currentName) {
            // 최신 잔액 가져와서 라벨 업데이트
            QString latestBalance = user.firstChildElement("Balance").text();
            ui->label_5->setText(latestBalance);
            break;
        }
    }
}


void UserWindow::on_pushButton_clicked()
{
    QString currentUserName = ui->label_2->text();
    sendDialog->setSenderInfo(currentUserName);
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

void UserWindow::setUserInfo(QString name, QString balance)
{
    ui->label_2->setText(name);
    ui->label_5->setText(balance);
}

void UserWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    refreshUserInfo();
}
