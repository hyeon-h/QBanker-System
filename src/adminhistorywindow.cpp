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

    ui->tableWidget->setColumnCount(5); // 5개 컬럼 확보
    ui->tableWidget->setHorizontalHeaderLabels({"날짜", "보낸 사람", "받는 사람", "금액", "설명"});
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // 모든 칸을 내용 크기에 맞춤
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);      // 마지막 '설명' 칸만 남은 공간 다 쓰기

    ui->spinBox->setMaximum(999999999);   //스핀박스 한도 해제
    ui->spinBox_2->setMaximum(999999999);

    ui->dateEdit->setDate(QDate(QDate::currentDate().year(),1,1));
    ui->dateEdit_2->setDate(QDate::currentDate());
}

AdminHistoryWindow::~AdminHistoryWindow()
{
    delete ui;
}

void AdminHistoryWindow::on_pushButton_clicked(){
    qDebug()<<"Ok";
}


void AdminHistoryWindow::on_pushButton_2_clicked(){
    qDebug()<<"Cancel";
    this->close();
}

void AdminHistoryWindow::closeEvent(QCloseEvent *event){
    parentWidget()->show();
    event->accept();
}

void AdminHistoryWindow::on_pushButton_3_clicked(){
    SearchCriteria sc;
    sc.useDate = ui->checkBox->isChecked(); //날짜 조건
    sc.start = ui->dateEdit->date();
    sc.end = ui->dateEdit_2->date();

    sc.useAmount = ui->checkBox_2->isChecked(); // 금액조건
    sc.minAmount = ui->spinBox->value();
    sc.maxAmount = ui->spinBox_2->value();

    sc.useUser = ui->checkBox_3->isChecked(); //사용자조건
    sc.userName = ui->lineEdit->text().trimmed();
    sc.typeIndex = ui->comboBox->currentIndex();

    filterAndDisplay(sc);
}

void AdminHistoryWindow::filterAndDisplay(const SearchCriteria& sc) {
    ui->tableWidget->setRowCount(0);
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

        // 3. 타입 필터 (0:전체, 1:입출금, 2:기타)
        if (sc.typeIndex == 1) {
            // 입출금: Transfer(송금) 내역만 통과
            if (h.action != ActionType::Transfer) continue;
        }
        else if (sc.typeIndex == 2) {
            // 기타: 계좌 생성(CreateAccount) 및 삭제(Delete)만 통과
            if (h.action == ActionType::Transfer) continue;
        }

        // 4. 사용자 필터 (체크박스 체크 시에만 작동)
        if (sc.useUser) {
            // 보낸 사람이나 받은 사람 중 검색어가 포함되어 있어야 함
            if (h.from != sc.userName && h.to != sc.userName) continue;
        }

        addTableRow(h);
    }
}

void AdminHistoryWindow::addTableRow(const History& h) {
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(h.dateTime.toString("yyyy-MM-dd HH:mm:ss")));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(h.from));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(h.to.isEmpty() ? "-" : h.to));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(h.amount) + "원")); // "원" 추가
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(getHistoryMessage(h))); // 상세 메시지
}

QString AdminHistoryWindow::getHistoryMessage(const History& h) {
    switch (h.action) {
    case ActionType::Transfer:
        return QString("[%1]님이 [%2]님에게 %3원을 송금했습니다.").arg(h.from).arg(h.to).arg(h.amount);
    case ActionType::CreateAccount:
        return QString("[%1]님이 계좌를 생성했습니다. (초기 입금: %2원)").arg(h.from).arg(h.amount);
    case ActionType::Delete:
        return QString("[%1]님의 계좌가 삭제되었습니다.").arg(h.from);
    default:
        return "알 수 없는 작업";
    }
}