#ifndef ADMINHISTORYWINDOW_H
#define ADMINHISTORYWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "history.h"

namespace Ui {
class AdminHistoryWindow;
}

class AdminHistoryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminHistoryWindow(QWidget *parent = nullptr);
    ~AdminHistoryWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::AdminHistoryWindow *ui;
    void filterAndDisplay(const SearchCriteria& sc);
    void addTableRow(const History& h);
};

#endif // ADMINHISTORYWINDOW_H
