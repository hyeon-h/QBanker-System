#include "senddialog.h"
#include "ui_senddialog.h"

SendDialog::SendDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SendDialog)
{
    ui->setupUi(this);
    setWindowTitle("Send");
}

SendDialog::~SendDialog()
{
    delete ui;
}

void SendDialog::on_pushButton_clicked()
{
    qDebug()<<"send";
    if(ui->lineEdit->text() == "")
    {
        ui->label_5->setText("목적지가 유효하지 않습니다.");
    }
    else if(ui->lineEdit_2->text().toInt() == 0)
    {
        ui->label_5->setText("금액이 유효하지 않습니다");
    }

}

void SendDialog::clearInputs()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->label_5->clear();
}

void SendDialog::on_pushButton_2_clicked()
{
    qDebug()<<"cancel";
    this->close();
}

void SendDialog::closeEvent(QCloseEvent *event)
{
    parentWidget()->show();
    event->accept();
}