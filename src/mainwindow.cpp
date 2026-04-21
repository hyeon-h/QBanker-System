#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userwindow.h"
#include "adminwindow.h"
#include "signup.h"
#include <QDomDocument>
#include <QFile>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("QBankerSystem");
    path = qApp->applicationDirPath() + "/../../../QBankerSystem";
    QDir().mkpath(path+ "/data");
    this->setFixedSize(550, 500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() {

    signupPage = new Signup(this);


    signupPage->setAttribute(Qt::WA_DeleteOnClose);


    signupPage->show();
}

void MainWindow::on_pushButton_2_clicked() {
    QString inputId = ui->lineEdit->text().trimmed();  // 공백 제거
    QString inputPw = ui->lineEdit_2->text();
    bool loginSuccess = false;

    // 1. 관리자 로그인 모드인지 확인
    if (ui->checkBox->isChecked()) {
        // [관리자 모드] XML을 뒤지지 않고 지정된 값으로 확인 (또는 관리자용 태그 확인)
        // 수동으로 추가한 admin 계정 정보를 여기서 체크합니다.
        if (inputId == "admin" && inputPw == "1234") {
            adminWin = new AdminWindow(this);
            ui->lineEdit_3->setText("관리자 모드로 로그인되었습니다.");
            // 관리자 전용 창 열기 로직 추가 가능
            adminWin->show();
            this->hide();
            return;
        } else {
            ui->lineEdit_3->setText("에러: 관리자 정보가 일치하지 않습니다.");
            return;
        }
    }

    // 2. 일반 유저 로그인 모드 (체크박스 해제 시)
    QFile file("../../data/user_data.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->lineEdit_3->setText("시스템 오류: 데이터베이스를 찾을 수 없습니다.");
        return;
    }

    QDomDocument doc;
    doc.setContent(&file);
    file.close();

    QDomNodeList users = doc.elementsByTagName("User");
    for (int i = 0; i < users.count(); ++i) {
        QDomElement userElement = users.at(i).toElement();
        QString xmlId = userElement.firstChildElement("Name").text();
        QString xmlPw = userElement.firstChildElement("Password").text();

        if (xmlId == inputId && xmlPw == inputPw) {
            loginSuccess = true;
            loginId = inputId;
            break;
        }
    }

    if (loginSuccess) {
        userWin = new UserWindow(this, loginId);
        ui->lineEdit_3->setText(inputId + "님, 로그인 성공!");
        userWin->show();
        this->hide();
        loadJson();
        //saveJson();
    } else {
        ui->lineEdit_3->setText("아이디 또는 비밀번호가 틀렸습니다.");
    }
}

void MainWindow::saveJson()
{
    History hist1; // 1. hist 생성
    hist1.dateTime = QDateTime(QDate(2026, 4, 21), QTime(15, 30, 0));
    hist1.from = "홍길동";
    hist1.amount = 50000;
    hist1.action = ActionType::Transfer;
    hist1.to = "김철수";

    History hist2;
    hist2.dateTime = QDateTime::currentDateTime();
    hist2.from = "김철수";
    hist2.amount = 1000;
    hist2.action = ActionType::Transfer;
    hist2.to = "홍길동";

    hists.push_back(hist1); // 2.vector에 추가
    hists.push_back(hist2);

    QJsonArray array; //3. jsonArray에 추가 (여기부터 저장)
    for(const History& h : std::as_const(hists)) // const User& u : u를 읽기전용으로 받음
    {                                            // std::as_const(users): users 컨테이너 자체를 읽기 전용으로 만듬.
        QJsonObject obj;
        obj["dateTime"] = h.dateTime.toString(Qt::ISODate); //ISO Date 규격으로 변환한 문자열을 저장
        obj["from"] = h.from;
        obj["amount"] = static_cast<qint64>(h.amount); // 1000은 기본적으로 int니까 qint64로 금액 범위 확장
        obj["action"] = static_cast<int>(h.action); // enum class를 저장하려면 정수로 저장해야함.
        obj["to"] = h.to;
        array.append(obj);
    }

    QJsonDocument doc(array); //4.jsondoc 생성 및 파일 write
    QString fileName = path + "/data/history.json";
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly)) return;
    file.write(doc.toJson());
    file.close();

}

void MainWindow::loadJson()
{
    QString fileName = path + "/data/history.json";
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly)) return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    hists.clear();

    QJsonArray array = doc.array();
    for(const QJsonValue& v: std::as_const(array))
    {
        QJsonObject obj = v.toObject();
        History hist;
        hist.dateTime = QDateTime::fromString((obj["dateTime"].toString()), Qt::ISODate);
        hist.from = obj["from"].toString();
        hist.amount = obj["amount"].toInt();
        hist.action = static_cast<ActionType>(obj["action"].toInt());
        hist.to = obj["to"].toString();
        hists.push_back(hist);
    }

    for(const History& h : std::as_const(hists))
    {
        qDebug()<<h.dateTime.toString("yyyy-MM-dd HH:mm:ss")<<h.from<< h.amount << static_cast<int>(h.action) << h.to;
    }
}