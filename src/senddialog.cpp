#include "senddialog.h"
#include "ui_senddialog.h"
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <QDebug>

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

void SendDialog::on_pushButton_clicked() // 'Send' 버튼
{
    // 1. 입력 데이터 가져오기
    QString receiverName = ui->lineEdit->text().trimmed();     // 수신자 이름
    int sendAmount = ui->lineEdit_2->text().toInt();          // 송금할 금액
    // ui->lineEdit_3는 예약 날짜용이니 지금은 무시합니다.

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
    }

    // 3. XML 파일 로드
    QFile file("../../data/user_data.xml");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        ui->label_5->setText("DB 파일을 열 수 없습니다.");
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

    // 입력창 깔끔하게 비우기 (예약 날짜 제외)
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