#include "meminfodialog.h"
#include "ui_meminfodialog.h"

MemInfoDialog::MemInfoDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MemInfoDialog)
{
    ui->setupUi(this);
    setWindowTitle("MemInfo");
}

MemInfoDialog::~MemInfoDialog()
{
    delete ui;
}

void MemInfoDialog::on_pushButton_clicked()
{
    qDebug()<<"Ok";
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