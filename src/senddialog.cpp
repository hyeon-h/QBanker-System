#include "senddialog.h"
#include "ui_senddialog.h"
#include <QFile>
#include <QDomDocument>
SendDialog::SendDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SendDialog)
{
    ui->setupUi(this);
    setWindowTitle("Send");
}

SendDialog::~SendDialog()
{
    delete ui;
}

void SendDialog::on_pushButton_clicked()
{
    bool userExists = false;
    bool moneyExist = false;
    int now_balance = 0;
    QString target = ui->lineEdit->text().trimmed();
    int amount = ui->lineEdit_2->text().toInt();
    if(target.isEmpty())
    {
        ui->label_5->setText("목적지가 유효하지 않습니다.");
        return;
    }

    if(amount <= 0)
    {
        ui->label_5->setText("금액이 유효하지 않습니다");
        return;
    }

    QFile file("../../data/user_data.xml");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        ui->label_5->setText("시스템 오류: 데이터 베이스를 찾을 수 없습니다");
        return;
    }
    QDomDocument doc;
    doc.setContent(&file);
    file.close();

    QDomNodeList users = doc.elementsByTagName("User");
    for(int i = 0; i<users.count(); ++i)
    {
        QDomElement userElement = users.at(i).toElement();
        QString xmlId = userElement.firstChildElement("Name").text();
        int xmlbl = userElement.firstChildElement("Balance").text().toInt();

        if(xmlId == DataManager::instance().loginId)
        {
            now_balance = xmlbl;
            if(now_balance>= amount)
            {
                moneyExist= true;
            }
        }

        if(xmlId == target)
        {
            userExists = true;
        }
    }

    if (!userExists)
    {
        ui->label_5->setText("에러: 존재하지 않는 사용자입니다");

    }
    else if(!moneyExist)
    {
        ui->label_5->setText("에러: 잔액이 부족합니다");
    }
    else
    {
        History hist; // 1. history 생성
        hist.dateTime = QDateTime::currentDateTime();
        hist.from = DataManager::instance().loginId;
        hist.amount = ui->lineEdit_2->text().toInt();
        hist.action = ActionType::Transfer;
        hist.to = target;
        DataManager::instance().addHistory(hist);

        ui->label_5->setText("송금 완료");

        ui->pushButton->setEnabled(false); // 중복 클릭 방지
        QTimer::singleShot(2000, this, SLOT(close()));
    }

}

void SendDialog::clearInputs()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->label_5->clear();
}

void SendDialog::on_pushButton_2_clicked()
{
    qDebug()<<"cancel";
    this->close();
}

void SendDialog::closeEvent(QCloseEvent *event)
{
    parentWidget()->show();
    event->accept();
}