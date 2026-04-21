#include "userhistorywindow.h"
#include "ui_userhistorywindow.h"

UserHistoryWindow::UserHistoryWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserHistoryWindow)
{
    ui->setupUi(this);
    setWindowTitle("UserHistory");
    ui->dateEdit->setDate(QDate(QDate::currentDate().year(),1,1));
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
    bool useDate = ui->checkBox->isChecked();
    bool useAmount= ui->checkBox_2->isChecked();

    if(useDate)
    {
        qDebug()<<"날짜 필터 사용 후 검색";
    }
    if(useAmount)
    {
        qDebug()<<"금액 필터 사용 후 검색";
    }
    qDebug()<<"검색";
}

