#ifndef USERHISTORYWINDOW_H
#define USERHISTORYWINDOW_H

#include <QMainWindow>

namespace Ui {
class UserHistoryWindow;
}

class UserHistoryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserHistoryWindow(QWidget *parent = nullptr);
    ~UserHistoryWindow();

private:
    Ui::UserHistoryWindow *ui;
};

#endif // USERHISTORYWINDOW_H
