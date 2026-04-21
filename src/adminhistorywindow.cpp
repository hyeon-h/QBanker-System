#include "adminhistorywindow.h"
#include "ui_adminhistorywindow.h"
#include "datamanager.h"
#include "history.h"

AdminHistoryWindow::AdminHistoryWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminHistoryWindow)
{
    ui->setupUi(this);
    DataManager::instance().loadJson();
    setWindowTitle("AdminHistory");
    ui->dateEdit->setDate(QDate(QDate::currentDate().year(),1,1));
    ui->dateEdit_2->setDate(QDate::currentDate());
}

AdminHistoryWindow::~AdminHistoryWindow()
{
    delete ui;
}

void AdminHistoryWindow::on_pushButton_clicked()
{
    qDebug()<<"Ok";
}


void AdminHistoryWindow::on_pushButton_2_clicked()
{
    qDebug()<<"Cancel";
    this->close();
}

void AdminHistoryWindow::closeEvent(QCloseEvent *event)
{
    parentWidget()->show();
    event->accept();
}

void AdminHistoryWindow::on_pushButton_3_clicked()
{
    SearchCriteria sc;

    // [날짜 조건] QDateEdit은 .date()로 바로 QDate를 가져옵니다.
    sc.useDate = ui->checkBox->isChecked();
    sc.start = ui->dateEdit->date();   // 시작 날짜
    sc.end = ui->dateEdit_2->date();    // 종료 날짜

    // [금액 조건]
    sc.useAmount = ui->checkBox_2->isChecked();
    sc.minAmount = ui->spinBox->value();
    sc.maxAmount = ui->spinBox_2->value();

    // [사용자 조건]
    sc.useUser = ui->checkBox_3->isChecked();
    sc.userName = ui->lineEdit->text().trimmed();
    sc.typeIndex = ui->comboBox->currentIndex();

    // 필터링 함수 실행
    filterAndDisplay(sc);

    qDebug() << "QDate 기반 검색 실행";
}

void AdminHistoryWindow::filterAndDisplay(const SearchCriteria& sc) {
    ui->tableWidget->setRowCount(0); // 검색 전 테이블 초기화

    // DataManager에서 전체 기록을 가져옴
    const auto& allHists = DataManager::instance().hists;

    for(const History& h : std::as_const(allHists)) {
        // 1. 날짜 필터
        if(sc.useDate) {
            if(h.dateTime.date() < sc.start || h.dateTime.date() > sc.end) continue;
        }

        // 2. 금액 필터
        if(sc.useAmount) {
            if(h.amount < sc.minAmount || h.amount > sc.maxAmount) continue;
        }

        // 3. 사용자 및 타입 필터
        if(sc.useUser) {
            bool isMatch = false;
            if(sc.typeIndex == 0) { // 전체
                if(h.from == sc.userName || h.to == sc.userName) isMatch = true;
            } else if(sc.typeIndex == 1) { // 보낸 사람만
                if(h.from == sc.userName) isMatch = true;
            } else if(sc.typeIndex == 2) { // 받은 사람만
                if(h.to == sc.userName) isMatch = true;
            }
            if(!isMatch) continue;
        }

        // 검문을 통과한 데이터만 테이블에 추가
        addTableRow(h);
    }
}

void AdminHistoryWindow::addTableRow(const History& h) {
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(h.dateTime.toString("yyyy-MM-dd HH:mm:ss")));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(h.from));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(h.to));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(h.amount)));
}
