#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "signup.h"


#include <QMainWindow>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QVector>
#include "userwindow.h"
#include "adminwindow.h"
#include <QStandardPaths>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

enum class ActionType {
    Transfer,
    CreateAccount
};

struct History
{
    QDateTime dateTime;
    QString from; // 송신자 or 가입자
    QString to; // 수신자
    ActionType action;
    qint64 amount;

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString path;
private slots:
    // UI에서 "Go to slot"으로 만든 함수들이 여기에 선언됩니다.
    void on_pushButton_clicked();   // 신규 가입 버튼
    void on_pushButton_2_clicked(); // 로그인 버튼

private:
    UserWindow* userWin;
    AdminWindow* adminWin;
    Ui::MainWindow *ui; // UI 부품들에 접근하기 위한 포인터
    Signup *signupPage;
    QVector<History> hists;
    void saveJson();
    void loadJson();
};

#endif // MAINWINDOW_H