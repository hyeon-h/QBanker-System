#include "userhistorywindow.h"
#include "ui_userhistorywindow.h"

UserHistoryWindow::UserHistoryWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserHistoryWindow)
{
    ui->setupUi(this);
}

UserHistoryWindow::~UserHistoryWindow()
{
    delete ui;
}
