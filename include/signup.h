#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QString>

namespace Ui {
class Signup;
}

class Signup : public QDialog
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

private slots:
    void on_buttonBox_accepted(); // OK 버튼 클릭 시 실행

private:
    Ui::Signup *ui;
    bool isIdDuplicated(QString id);
    void saveToXml(QString id, QString pw, int deposit);
};

#endif