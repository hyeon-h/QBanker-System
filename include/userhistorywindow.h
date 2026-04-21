#ifndef USERHISTORYWINDOW_H
#define USERHISTORYWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class UserHistoryWindow;
}

class UserHistoryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserHistoryWindow(QWidget *parent = nullptr, QString id = "");
    ~UserHistoryWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

protected:
    void closeEvent(QCloseEvent *event) override;
private:
    QString loginId;
    Ui::UserHistoryWindow *ui;
};

#endif // USERHISTORYWINDOW_H
