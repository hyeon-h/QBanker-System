#include "adminhistorywindow.h"
#include "ui_adminhistorywindow.h"

AdminHistoryWindow::AdminHistoryWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminHistoryWindow)
{
    ui->setupUi(this);
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
    bool useDate = ui->checkBox->isChecked();
    bool useAmount= ui->checkBox_2->isChecked();
    bool usePeople = ui->checkBox_3->isChecked();

    if(useDate)
    {
        qDebug()<<"날짜 필터 사용 후 검색";
    }
    if(useAmount)
    {
        qDebug()<<"금액 필터 사용 후 검색";
    }
    if(usePeople)
    {
        qDebug()<<"전체 검색";
    }
    qDebug()<<"검색";
}

