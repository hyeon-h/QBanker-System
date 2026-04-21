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
    userWin = new UserWindow(this);
    adminWin = new AdminWindow(this);
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
            break;
        }
    }

    if (loginSuccess) {
        ui->lineEdit_3->setText(inputId + "님, 로그인 성공!");
        userWin->show();
        this->hide();
    } else {
        ui->lineEdit_3->setText("아이디 또는 비밀번호가 틀렸습니다.");
    }
}
