#include "senddialog.h"
#include "ui_senddialog.h"

SendDialog::SendDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SendDialog)
{
    ui->setupUi(this);
}

SendDialog::~SendDialog()
{
    delete ui;
}

void SendDialog::on_pushButton_clicked()
{
    qDebug()<<"send";
    this->close();
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