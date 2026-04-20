#include "adminhistorywindow.h"
#include "ui_adminhistorywindow.h"

AdminHistoryWindow::AdminHistoryWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminHistoryWindow)
{
    ui->setupUi(this);
}

AdminHistoryWindow::~AdminHistoryWindow()
{
    delete ui;
}
