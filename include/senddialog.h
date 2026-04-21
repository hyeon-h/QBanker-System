#ifndef SENDDIALOG_H
#define SENDDIALOG_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class SendDialog;
}

class SendDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SendDialog(QWidget *parent = nullptr);
    ~SendDialog();
    void clearInputs();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    void closeEvent(QCloseEvent *event) override;
    Ui::SendDialog *ui;

private:
    QString senderName; // 돈 보내는 사람 이름 저장

public:
    void setSenderInfo(QString name); // 이름 받아오는 통로
};

#endif // SENDDIALOG_H
