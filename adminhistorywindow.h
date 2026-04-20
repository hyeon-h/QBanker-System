#ifndef ADMINHISTORYWINDOW_H
#define ADMINHISTORYWINDOW_H

#include <QMainWindow>

namespace Ui {
class AdminHistoryWindow;
}

class AdminHistoryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminHistoryWindow(QWidget *parent = nullptr);
    ~AdminHistoryWindow();

private:
    Ui::AdminHistoryWindow *ui;
};

#endif // ADMINHISTORYWINDOW_H
