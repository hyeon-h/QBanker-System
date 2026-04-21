#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include "senddialog.h"
#include "userhistorywindow.h"

namespace Ui {
class UserWindow;
}

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent = nullptr, QString id ="");
    ~UserWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    QString loginId;
    SendDialog* sendDialog;
    UserHistoryWindow* userHistoryWindow;
    Ui::UserWindow *ui;
};

#endif // UserWindow_H
