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
    this->setFixedSize(550, 500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() {

    signupPage = new Signup(this);


    signupPage->setAttribute(Qt::WA_DeleteOnClose);


    signupPage->exec();
}

void MainWindow::on_pushButton_2_clicked() {
    // 1. 입력 데이터 수집 및 공백 제거
    QString inputId = ui->lineEdit->text().trimmed();
    QString inputPw = ui->lineEdit_2->text();
    bool loginSuccess = false;

    // 2. 관리자 로그인 모드 확인 (체크박스 활성화 시)
    if (ui->checkBox->isChecked()) {
        if (inputId == "admin" && inputPw == "1234") {
            ui->lineEdit_3->setText("관리자 모드로 로그인되었습니다.");

            // [주의] 여기서 adminWin을 중복 생성(new)하고 계셨습니다. 하나는 정리하는 게 좋습니다.
            adminWin = new AdminWindow(this);
            adminWin->show();
            this->hide();
            return;
        } else {
            ui->lineEdit_3->setText("에러: 관리자 정보가 일치하지 않습니다.");
            return;
        }
    }

    // 3. 일반 사용자 로그인: XML 데이터베이스 로드
    QFile file("../../data/user_data.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->lineEdit_3->setText("시스템 오류: 데이터베이스를 찾을 수 없습니다.");
        return;
    }

    QDomDocument doc;
    doc.setContent(&file);
    file.close();

    // 4. 모든 User 노드를 순회하며 계정 정보 대조
    QDomNodeList users = doc.elementsByTagName("User");
    for (int i = 0; i < users.count(); ++i) {
        QDomElement userElement = users.at(i).toElement();
        QString xmlId = userElement.firstChildElement("Name").text();
        QString xmlPw = userElement.firstChildElement("Password").text();
        QString xmlActiveStr = userElement.firstChildElement("IsActive").text();

        // 아이디와 비밀번호가 일치하는지 확인
        if (xmlId == inputId && xmlPw == inputPw ) {
            // 계정 활성화 상태(IsActive) 확인
            if(xmlActiveStr == "true") {
                QString xmlBalance = userElement.firstChildElement("Balance").text();

                // 싱글톤 데이터 매니저에 로그인 정보 저장 및 JSON 로드
                DataManager::instance().loginId = inputId;
                DataManager::instance().loadJson();

                // 사용자 윈도우 생성 및 정보 전달
                userWin = new UserWindow(this);
                userWin->setUserInfo(xmlId, xmlBalance);
                userWin->show();
                this->hide();

                loginSuccess = true;
                break; // 일치하는 유저를 찾았으므로 루프 종료
            } else {
                // 비활성 계정 처리
                ui->lineEdit_3->setText(inputId + "님, 현재 비활성화중 입니다. 관리자에게 문의하세요!");
                return;
            }
        }
    }

    // 5. 로그인 실패 시 메시지 출력
    if (loginSuccess == false) {
        ui->lineEdit_3->setText("아이디 또는 비밀번호가 틀렸습니다.");
    }
}