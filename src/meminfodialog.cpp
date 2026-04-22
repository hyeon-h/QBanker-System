#include "meminfodialog.h"
#include "ui_meminfodialog.h"
#include <QFile>
#include <QDomDocument>
#include <QTableWidgetItem>

MemInfoDialog::MemInfoDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MemInfoDialog)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setWindowTitle("MemInfo");
    loadUserData();
}

MemInfoDialog::~MemInfoDialog()
{
    delete ui;
}

void MemInfoDialog::loadUserData() {
    // 1. 유저 데이터 XML 파일 열기
    QFile file("../../data/user_data.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    // 2. XML 문서 구조화 (파싱)
    QDomDocument doc;
    if (!doc.setContent(&file)) {
        file.close();
        return;
    }
    file.close(); // 파싱이 끝났으므로 파일은 즉시 닫음

    // 3. 테이블 초기화
    ui->tableWidget->setRowCount(0);

    // 4. "User" 태그를 가진 모든 노드 추출
    QDomNodeList users = doc.elementsByTagName("User");

    for (int i = 0; i < users.count(); ++i) {
        QDomNode userNode = users.at(i);
        if (userNode.isElement()) {
            QDomElement userElement = userNode.toElement();

            // XML 엘리먼트에서 텍스트 데이터 추출
            QString id = userElement.firstChildElement("Name").text();
            QString balance = userElement.firstChildElement("Balance").text();
            QString date = userElement.firstChildElement("JoinDate").text();
            QString pw = userElement.firstChildElement("Password").text();
            QString active = userElement.firstChildElement("IsActive").text();

            // 5. 테이블 행 추가 및 아이템 배치
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);

            // 첫 번째 열(이름)에 체크박스 기능 포함
            QTableWidgetItem *nameItem = new QTableWidgetItem(id);
            nameItem->setCheckState(Qt::Unchecked);

            ui->tableWidget->setItem(row, 0, nameItem);
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(balance));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(date));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(pw));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(active));
        }
    }

    // 모든 열의 너비를 내용에 맞게 자동 조절
    ui->tableWidget->resizeColumnsToContents();
}

void MemInfoDialog::on_pushButton_clicked(){
    this->accept();
}


void MemInfoDialog::on_pushButton_2_clicked(){
    this->close();
}

void MemInfoDialog::closeEvent(QCloseEvent *event){
    parentWidget()->show();
    event->accept();
}
void MemInfoDialog::on_pushButton_3_clicked(){
    // 1. XML 파일 읽기
    QFile file("../../data/user_data.xml");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) return;

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        file.close();
        return;
    }

    QDomNodeList userNodes = doc.elementsByTagName("User");
    bool isChanged = false;

    // 2. 테이블의 모든 행을 확인
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        // 체크박스가 체크된 행만 처리
        if (ui->tableWidget->item(i, 0)->checkState() == Qt::Checked) {
            QString targetName = ui->tableWidget->item(i, 0)->text();

            // 3. XML에서 해당 사용자를 찾아서 상태 반전
            for (int j = 0; j < userNodes.count(); ++j) {
                QDomElement userElem = userNodes.at(j).toElement();

                if (userElem.firstChildElement("Name").text() == targetName) {
                    // 현재 상태 읽기
                    QString currentStatus = userElem.firstChildElement("IsActive").text();

                    // 상태 반전 로직 (true -> false, false -> true)
                    QString newStatus = (currentStatus == "true") ? "false" : "true";

                    // XML 데이터 수정
                    userElem.firstChildElement("IsActive").firstChild().setNodeValue(newStatus);

                    // 4. UI 테이블에도 즉시 반영
                    ui->tableWidget->item(i, 4)->setText(newStatus);

                    isChanged = true;
                    break;
                }
            }
        }
    }

    // 5. 변경사항이 있으면 파일에 다시 저장
    if (isChanged) {
        file.resize(0); // 기존 내용 비우기
        QTextStream out(&file);
        doc.save(out, 4);
    }

    file.close();

    // 선택 해제 (깔끔하게 마무리)
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        ui->tableWidget->item(i, 0)->setCheckState(Qt::Unchecked);
    }
}

