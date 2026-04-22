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

void MemInfoDialog::loadUserData()
{
    QFile file("../../data/user_data.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        file.close();
        return;
    }
    file.close();


    ui->tableWidget->setRowCount(0);



    QDomNodeList users = doc.elementsByTagName("User");

    for (int i = 0; i < users.count(); ++i) {
        QDomNode userNode = users.at(i);
        if (userNode.isElement()) {
            QDomElement userElement = userNode.toElement();


            QString id = userElement.firstChildElement("Name").text();
            QString balance = userElement.firstChildElement("Balance").text();
            QString date = userElement.firstChildElement("JoinDate").text();
            QString pw = userElement.firstChildElement("Password").text();
            QString active = userElement.firstChildElement("IsActive").text();


            int row = ui->tableWidget->rowCount();
            QTableWidgetItem *nameItem = new QTableWidgetItem(id);
            nameItem->setCheckState(Qt::Unchecked); // 이 코드가 체크박스를 만듭니다.

            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, nameItem);
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(balance));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(date));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(pw));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(active));
        }
    }


    ui->tableWidget->resizeColumnsToContents();
}

void MemInfoDialog::on_pushButton_clicked()
{
    qDebug()<<"Ok";
    this->accept();
}


void MemInfoDialog::on_pushButton_2_clicked()
{
    qDebug()<<"Cancel";
    this->close();
}

void MemInfoDialog::closeEvent(QCloseEvent *event)
{
    parentWidget()->show();
    event->accept();
}
void MemInfoDialog::on_pushButton_3_clicked()
{
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
        qDebug() << "사용자 활성화 상태 변경 완료!";
    }

    file.close();

    // 선택 해제 (깔끔하게 마무리)
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        ui->tableWidget->item(i, 0)->setCheckState(Qt::Unchecked);
    }
}

