#ifndef USERHISTORYWINDOW_H
#define USERHISTORYWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "history.h"

namespace Ui {
class UserHistoryWindow;
}

class UserHistoryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserHistoryWindow(QWidget *parent = nullptr);
    ~UserHistoryWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

protected:
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::UserHistoryWindow *ui;
    void filterAndDisplay(const SearchCriteria& sc);
    void addTableRow(const History& h);
    QString getUserMessage(const History& h);
};

#endif // USERHISTORYWINDOW_H
