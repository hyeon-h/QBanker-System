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

void UserHistoryWindow::on_pushButton_clicked(){
    qDebug()<<"ok";
}

void UserHistoryWindow::on_pushButton_2_clicked(){
    qDebug()<<"cancel";
    this->close();
}

void UserHistoryWindow::closeEvent(QCloseEvent *event){
    parentWidget()->show();
    event->accept();
}

void UserHistoryWindow::on_pushButton_3_clicked() {
    SearchCriteria sc;

    // 1. 날짜 필터 조건 수집
    sc.useDate = ui->checkBox->isChecked();
    sc.start = ui->dateEdit->date();
    sc.end = ui->dateEdit_2->date();

    // 2. 금액 필터 조건 수집
    sc.useAmount = ui->checkBox_2->isChecked();
    sc.minAmount = ui->spinBox->value();
    sc.maxAmount = ui->spinBox_2->value();

    // 3. 거래 유형(전체/송금/입금) 인덱스 수집
    sc.typeIndex = ui->comboBox->currentIndex();

    // 수집된 조건을 기반으로 필터링 및 출력 실행
    filterAndDisplay(sc);
}

void UserHistoryWindow::filterAndDisplay(const SearchCriteria& sc) {
    // 기존 테이블 내역 초기화 (새로운 검색 결과를 위해)
    ui->tableWidget->setRowCount(0);

    // 데이터 원본 및 로그인 정보 가져오기
    const auto& allHists = DataManager::instance().hists;
    QString loginId = DataManager::instance().loginId;

    for(const History& h : std::as_const(allHists)) {
        // [보안 필터] 본인이 보낸 것도 아니고, 받은 것도 아니면 남의 내역이므로 즉시 제외
        if(h.from != loginId && h.to != loginId) continue;

        // [송수신 종류 필터] 콤보박스 선택값에 따른 분기 처리
        if(sc.typeIndex == 1) { // '송금'만 보기: 발신자가 본인이 아닌 경우 제외
            if(h.from != loginId) continue;
        } else if(sc.typeIndex == 2) { // '입금'만 보기: 수신자가 본인이 아닌 경우 제외
            if(h.to != loginId) continue;
        }

        // [날짜 필터] 체크박스 활성화 시 기간 내에 포함되는지 검사
        if(sc.useDate) {
            if(h.dateTime.date() < sc.start || h.dateTime.date() > sc.end) continue;
        }

        // [금액 필터] 체크박스 활성화 시 설정한 최소/최대 금액 범위 검사
        if(sc.useAmount) {
            if(h.amount < sc.minAmount || h.amount > sc.maxAmount) continue;
        }

        // 모든 필터를 통과한 데이터만 테이블 행으로 추가
        addTableRow(h);
    }
}

void UserHistoryWindow::addTableRow(const History& h) { //필터링된 History 객체를 테이블 위젯의 한 행(Row)으로 변환하여 추가.
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    // 각 열(Column)에 데이터 배치
    // 0: 일시, 1: 발신자, 2: 수신자(없으면 -), 3: 금액, 4: 상세 메시지
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(h.dateTime.toString("yyyy-MM-dd HH:mm:ss")));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(h.from));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(h.to.isEmpty() ? "-" : h.to));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(h.amount) + "원"));

    // getUserMessage(h)를 통해 "누구님께 송금" 또는 "누구님께 입금" 등의 메시지 생성 후 출력
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
    return "기타";
}


