#ifndef MEMINFODIALOG_H
#define MEMINFODIALOG_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class MemInfoDialog;
}

class MemInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MemInfoDialog(QWidget *parent = nullptr);
    ~MemInfoDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    void closeEvent(QCloseEvent *event) override;
    void loadUserData();

    Ui::MemInfoDialog *ui;
};

#endif // MEMINFODIALOG_H
