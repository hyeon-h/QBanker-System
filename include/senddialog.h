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
    QString senderName;

public:
    void setSenderInfo(QString name);
};

#endif
