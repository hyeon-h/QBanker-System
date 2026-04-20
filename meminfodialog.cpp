#include "meminfodialog.h"
#include "ui_meminfodialog.h"

MemInfoDialog::MemInfoDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MemInfoDialog)
{
    ui->setupUi(this);
}

MemInfoDialog::~MemInfoDialog()
{
    delete ui;
}
