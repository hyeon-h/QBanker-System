#include "signup.h"
#include "form/ui_signup.h"
#include <QFile>
#include <QDomDocument> // XML 읽기용
#include <QXmlStreamWriter> // XML 쓰기용
#include <QDomElement>
#include <QDomNodeList>
#include <QDatetime>
#include <QTimer>
#include "history.h"
#include "datamanager.h"

Signup::Signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signup) // UI 객체 동적 할당
{
    ui->setupUi(this); // 디자인(.ui) 파일의 내용을 이 클래스에 입힘
}

// 소멸자: 객체가 없어질 때 메모리를 해제함
Signup::~Signup()
{
    delete ui; // 할당했던 UI 객체 삭제 (메모리 관리)
}

void Signup::on_buttonBox_accepted() {
    // 1. 버퍼에 일시 저장 (변수에 담기)
    QString id = ui->lineEdit_2->text().trimmed(); // 앞뒤 공백 제거
    QString pw1 = ui->lineEdit_3->text();
    QString pw2 = ui->lineEdit_4->text();
    int deposit = ui->spinBox->value();

    ui->lineEdit->clear();
   ui->lineEdit->setEnabled(false);

    // 2. 입력란 비어있는지 기본 검사
    if(id.isEmpty() || pw1.isEmpty() || pw2.isEmpty()) {
        ui->lineEdit->setText("에러: 초기 입금액을 제외한 모든 항목을 입력해주세요.");
        return;
    }

    // 3. 비밀번호 불일치 검사
    if (pw1 != pw2) {
        ui->lineEdit->setText("에러: 비밀번호가 일치하지 않습니다.");
        return;
    }

    // 4. ID 중복 검사
    if (isIdDuplicated(id)) {
        ui->lineEdit->setText("에러: 이미 존재하는 아이디입니다.");
        return;
    }

    // 5. 검증 통과 시 XML 저장
    saveToXml(id, pw1, deposit);
}

void Signup::saveToXml(QString id, QString pw, int deposit) {
    QFile file("../../data/user_data.xml");
    QDomDocument doc;
    QDomElement root;

    // 현재 날짜 및 시간 생성 (포맷: 2026-04-20 17:30:00)
    QString signupDate = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString isActive = "true"; // 신규 가입 시 기본 활성화

    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        doc.setContent(&file);
        root = doc.documentElement();
        file.close();
    } else {
        root = doc.createElement("Users");
        doc.appendChild(root);
    }

    // 유저 데이터 노드 생성
    QDomElement user = doc.createElement("User");

    // 요구하신 포맷 적용
    QDomElement nameNode = doc.createElement("Name");
    nameNode.appendChild(doc.createTextNode(id));

    QDomElement dateNode = doc.createElement("JoinDate");
    dateNode.appendChild(doc.createTextNode(signupDate));

    QDomElement pwNode = doc.createElement("Password");
    pwNode.appendChild(doc.createTextNode(pw));

    QDomElement balanceNode = doc.createElement("Balance");
    balanceNode.appendChild(doc.createTextNode(QString::number(deposit)));
    user.appendChild(balanceNode);

    QDomElement activeNode = doc.createElement("IsActive");
    activeNode.appendChild(doc.createTextNode(isActive));

    user.appendChild(nameNode);
    user.appendChild(dateNode);
    user.appendChild(pwNode);
    user.appendChild(balanceNode);
    user.appendChild(activeNode);
    root.appendChild(user);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        // doc.toString(4)를 하면 4칸 들여쓰기가 적용되어
        // 엑셀의 행/열 구분처럼 가독성이 확 올라갑니다.
        stream << doc.toString(4);

        file.close();

        History h;
        h.dateTime = QDateTime::currentDateTime();
        h.from = id;               // 가입자 ID
        h.to = "";                 // 가입은 수신자 없음
        h.action = ActionType::CreateAccount;
        h.amount = deposit;        // 초기 입금액

        DataManager::instance().addHistory(h);

        ui->lineEdit->setText("회원가입 완료: [" + id + "]님 환영합니다.");
        QTimer::singleShot(2000, this, &Signup::accept);
    }
}

// 중복 검사 로직 (기존과 동일)
bool Signup::isIdDuplicated(QString id) {
    QFile file("user_data.xml");
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) return false;

    QDomDocument doc;
    doc.setContent(&file);
    file.close();

    QDomNodeList names = doc.elementsByTagName("Name");
    for (int i = 0; i < names.count(); ++i) {
        if (names.at(i).toElement().text() == id) return true;
    }
    return false;
}