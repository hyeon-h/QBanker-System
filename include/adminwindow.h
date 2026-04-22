#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include "adminhistorywindow.h"
#include "meminfodialog.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    AdminHistoryWindow* adminHistoryWindow;
    MemInfoDialog* memInfoDialog;
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
