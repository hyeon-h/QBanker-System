#include "userhistorywindow.h"
#include "ui_userhistorywindow.h"
#include "datamanager.h"
#include "history.h"
#include <QTableWidgetItem>
#include <QHeaderView>

UserHistoryWindow::UserHistoryWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserHistoryWindow)
{
    ui->setupUi(this);
    setWindowTitle("UserHistory");

    DataManager::instance().loadJson(); // 데이터 로드

    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels({"날짜", "보낸 사람", "받는 사람", "금액", "결과"});

    // 컬럼 너비 설정 (설명 칸은 길게, 나머지는 내용에 맞게)
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);

    // 스핀박스 한도 해제 (9억)
    ui->spinBox->setMaximum(999999999);
    ui->spinBox_2->setMaximum(999999999);

    // 날짜 초기값 (올해 1월 1일부터 오늘까지)
    ui->dateEdit->setDate(QDate(QDate::currentDate().year(), 1, 1));
    ui->dateEdit_2->setDate(QDate::currentDate());
}

UserHistoryWindow::~UserHistoryWindow()
{
    delete ui;
}

void UserHistoryWindow::on_pushButton_clicked()
{
    qDebug()<<"ok";
}

void UserHistoryWindow::on_pushButton_2_clicked()
{
    qDebug()<<"cancel";
    this->close();
}

void UserHistoryWindow::closeEvent(QCloseEvent *event)
{
    parentWidget()->show();
    event->accept();
}

void UserHistoryWindow::on_pushButton_3_clicked()
{
    SearchCriteria sc;
    sc.useDate = ui->checkBox->isChecked();
    sc.start = ui->dateEdit->date();
    sc.end = ui->dateEdit_2->date();

    sc.useAmount = ui->checkBox_2->isChecked();
    sc.minAmount = ui->spinBox->value();
    sc.maxAmount = ui->spinBox_2->value();

    sc.typeIndex = ui->comboBox->currentIndex();

    filterAndDisplay(sc);
}

void UserHistoryWindow::filterAndDisplay(const SearchCriteria& sc) {
    ui->tableWidget->setRowCount(0);
    const auto& allHists = DataManager::instance().hists;
    QString loginId = DataManager::instance().loginId; // 현재 로그인된 주인님 ID

    for(const History& h : std::as_const(allHists)) {
        // [보안 필터] 일단 나와 관련 없는 내역은 무조건 탈락
        if(h.from != loginId && h.to != loginId) continue;

        // [송수신 종류 필터] 콤보박스 선택에 따라 한 번 더 거르기
        if(sc.typeIndex == 1) { // 송금만 보기
            if(h.from != loginId) continue;
        } else if(sc.typeIndex == 2) { // 입금만 보기
            if(h.to != loginId) continue;
        }

        // [날짜 필터]
        if(sc.useDate) {
            if(h.dateTime.date() < sc.start || h.dateTime.date() > sc.end) continue;
        }

        // [금액 필터]
        if(sc.useAmount) {
            if(h.amount < sc.minAmount || h.amount > sc.maxAmount) continue;
        }

        addTableRow(h);
    }
}

void UserHistoryWindow::addTableRow(const History& h) {
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(h.dateTime.toString("yyyy-MM-dd HH:mm:ss")));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(h.from));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(h.to.isEmpty() ? "-" : h.to));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(h.amount) + "원"));

    // 유저 상황에 맞는 메시지 생성
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(getUserMessage(h)));
}

QString UserHistoryWindow::getUserMessage(const History& h) {
    QString loginId = DataManager::instance().loginId;

    if (h.action == ActionType::Transfer) {
        if (h.from == loginId) {
            // 내가 보낸 경우 (송금)
            return QString("[%1]님께 %2원 송금 완료").arg(h.to).arg(h.amount);
        } else {
            // 내가 받은 경우 (입금)
            return QString("[%1]님으로부터 %2원 입금 완료").arg(h.from).arg(h.amount);
        }
    } else if (h.action == ActionType::CreateAccount) {
        return "계좌 생성 및 초기 입금 축하드립니다.";
    }
    return "기타 거래";
}


