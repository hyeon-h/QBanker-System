#include "userwindow.h"
#include "ui_userwindow.h"
#include "senddialog.h"
#include "userhistorywindow.h"
#include <QMessageBox>
#include "history.h"
#include "datamanager.h"
#include <QFile>
#include <QDomDocument>
#include <QTextStream>

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

void UserWindow::refreshUserInfo(){
    QString currentName = ui->label_2->text();

    QFile file("../../data/user_data.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QDomDocument doc;
    doc.setContent(&file);
    file.close();

    QDomNodeList users = doc.elementsByTagName("User");
    for (int i = 0; i < users.count(); ++i) {
        QDomElement user = users.at(i).toElement();
        if (user.firstChildElement("Name").text() == currentName) {

            QString latestBalance = user.firstChildElement("Balance").text();
            ui->label_5->setText(latestBalance);
            break;
        }
    }
}


void UserWindow::on_pushButton_clicked(){
    QString currentUserName = ui->label_2->text();
    sendDialog = new SendDialog(this);
    sendDialog->setSenderInfo(currentUserName);
    sendDialog->setAttribute(Qt::WA_DeleteOnClose);
    
    sendDialog->clearInputs();
    sendDialog->exec();
    refreshUserInfo();
}


void UserWindow::on_pushButton_2_clicked(){
    userHistoryWindow = new UserHistoryWindow(this);
    userHistoryWindow->setAttribute(Qt::WA_DeleteOnClose);
    userHistoryWindow->show();
}


void UserWindow::on_pushButton_3_clicked(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "회원 탈퇴",
                                  "정말로 탈퇴하시겠습니까? 모든 정보가 삭제됩니다.",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        History h;
        h.dateTime = QDateTime::currentDateTime();
        h.from = DataManager::instance().loginId;
        h.to = "";
        h.action = ActionType::Delete;
        h.amount = 0;

        DataManager::instance().addHistory(h);
        QString currentName = ui->label_2->text();

        // 1. XML 파일 열기
        QFile file("../../data/user_data.xml");
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QMessageBox::critical(this, "오류", "데이터베이스를 열 수 없습니다.");
            return;
        }

        QDomDocument doc;
        if (!doc.setContent(&file)) {
            file.close();
            return;
        }

        // 2. 루트 노드(<Users> 같은 최상위 태그) 가져오기
        QDomElement root = doc.documentElement();
        QDomNodeList users = doc.elementsByTagName("User");
        bool found = false;

        // 3. 루프를 돌며 삭제 대상 찾기
        for (int i = 0; i < users.count(); ++i) {
            QDomElement user = users.at(i).toElement();
            if (user.firstChildElement("Name").text() == currentName) {
                // 부모 노드(root)에서 이 자식(user)을 삭제
                root.removeChild(user);
                found = true;
                break;
            }
        }

        if (found) {
            // 4. 파일 갱신 (리사이즈 후 저장)
            file.resize(0);
            QTextStream out(&file);
            doc.save(out, 4);
            file.close();

            QMessageBox::information(this, "탈퇴 완료", "그동안 이용해주셔서 감사합니다.");

            // 5. 창 닫고 로그인 화면으로 튕겨내기
            this->close(); // 현재 창 닫기 (closeEvent가 있으면 MainWindow가 뜰 겁니다)
            // 만약 closeEvent를 따로 안 만드셨다면 parentWidget()->show(); 를 명시적으로 호출하세요.
            if(parentWidget()) parentWidget()->show();
        } else {
            file.close();
            QMessageBox::warning(this, "오류", "사용자 정보를 찾을 수 없습니다.");
        }
    }
}

void UserWindow::setUserInfo(QString name, QString balance){
    ui->label_2->setText(name);
    ui->label_5->setText(balance);
}

void UserWindow::showEvent(QShowEvent *event){
    QMainWindow::showEvent(event);
    refreshUserInfo();
}
