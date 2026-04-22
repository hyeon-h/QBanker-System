#include "adminwindow.h"
#include "ui_adminwindow.h"
#include <QFile>
#include <QDomDocument>

AdminWindow::AdminWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    setWindowTitle("AdminLogin");
<<<<<<< HEAD
=======


    QFile file("../../data/user_data.xml");
    int userCount = 0;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QDomDocument doc;
        if (doc.setContent(&file)) {

            QDomNodeList users = doc.elementsByTagName("User");
            userCount = users.count();
        }
        file.close();
    }


    ui->lineEdit->setText(QString::number(userCount));
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setAlignment(Qt::AlignCenter);

    adminHistoryWindow = new AdminHistoryWindow(this);
    memInfoDialog = new MemInfoDialog(this);
>>>>>>> feat/user
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_pushButton_clicked()
{
    qDebug()<<"가입자 조회";
<<<<<<< HEAD
    memInfoDialog = new MemInfoDialog(this);
    memInfoDialog->setAttribute(Qt::WA_DeleteOnClose);
    memInfoDialog->show();
=======
    memInfoDialog->exec();
    //this->hide();
>>>>>>> feat/user
}

void AdminWindow::on_pushButton_2_clicked()
{
    qDebug()<<"입출금 내역";
    adminHistoryWindow = new AdminHistoryWindow(this);
    adminHistoryWindow->setAttribute(Qt::WA_DeleteOnClose);
    adminHistoryWindow->show();
<<<<<<< HEAD
=======
    //this->hide();
>>>>>>> feat/user
}