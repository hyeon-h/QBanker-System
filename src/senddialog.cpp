#include "senddialog.h"
#include "ui_senddialog.h"
#include <QFile>
#include <QDomDocument>
<<<<<<< HEAD
=======
#include <QTextStream>
#include <QDebug>

>>>>>>> feat/user
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
<<<<<<< HEAD
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
=======
    // 1. 입력 데이터 가져오기
    QString receiverName = ui->lineEdit->text().trimmed();
    int sendAmount = ui->lineEdit_2->text().toInt();


    // 2. 기초 유효성 검사 (label_5에 상태 표시)
    if (receiverName.isEmpty()) {
        ui->label_5->setText("수신자 이름을 입력해주세요.");
        return;
    }
    if (sendAmount <= 0) {
        ui->label_5->setText("송금할 금액을 정확히 입력해주세요.");
        return;
    }
    if (receiverName == senderName) {
        ui->label_5->setText("본인에게는 송금할 수 없습니다.");
        return;
>>>>>>> feat/user
    }

    // 3. XML 파일 로드
    QFile file("../../data/user_data.xml");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        ui->label_5->setText("XML 파일을 열 수 없습니다.");
        return;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        ui->label_5->setText("XML 구조를 읽을 수 없습니다.");
        file.close();
        return;
    }

    QDomNodeList users = doc.elementsByTagName("User");
    QDomElement senderElem;
    QDomElement receiverElem;
    bool receiverFound = false;

    // 4. 발신자와 수신자 찾기
    for (int i = 0; i < users.count(); ++i) {
        QDomElement user = users.at(i).toElement();
        QString name = user.firstChildElement("Name").text();

        if (name == senderName) {
            senderElem = user;
        }
        if (name == receiverName) {
            receiverElem = user;
            receiverFound = true;
        }
    }

    // 5. 비즈니스 로직 검사
    if (!receiverFound) {
        ui->label_5->setText("수신자를 찾을 수 없습니다.");
        file.close();
        return;
    }

    int currentSenderBalance = senderElem.firstChildElement("Balance").text().toInt();
    if (currentSenderBalance < sendAmount) {
        ui->label_5->setText("잔액이 부족합니다. (현재: " + QString::number(currentSenderBalance) + "원)");
        file.close();
        return;
    }

    // 6. 실제 데이터 수정 (핵심!)
    int currentReceiverBalance = receiverElem.firstChildElement("Balance").text().toInt();

    // 내 잔액 깎기
    senderElem.firstChildElement("Balance").firstChild().setNodeValue(QString::number(currentSenderBalance - sendAmount));

    // 상대방 잔액 올리기
    receiverElem.firstChildElement("Balance").firstChild().setNodeValue(QString::number(currentReceiverBalance + sendAmount));

    // 7. 파일 저장 (덮어쓰기)
    file.resize(0); // 기존 파일 내용 초기화
    QTextStream out(&file);
    doc.save(out, 4);
    file.close();

    // 8. 결과 알림
    ui->label_5->setText(receiverName + "님께 " + QString::number(sendAmount) + "원 송금 완료!");


    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
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

void SendDialog::setSenderInfo(QString name) {
    this->senderName = name;
    qDebug() << "발신자 확인:" << senderName;
}