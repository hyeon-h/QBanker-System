#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "signup.h"
#include "datamanager.h"
#include "history.h"
#include <QMainWindow>
#include "userwindow.h"
#include "adminwindow.h"
#include <QStandardPaths>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
// 프로그램 시작 메인 화면: 로그인 및 회원가입 접근 제어
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();   // 신규 회원가입 창(Signup) 호출
    void on_pushButton_2_clicked(); // 사용자/관리자 로그인 로직 수행

private:
    UserWindow* userWin;            // 일반 사용자 전용 메인 화면 객체
    AdminWindow* adminWin;          // 관리자 전용 메인 화면 객체
    Ui::MainWindow *ui;             // 메인 화면 UI 인터페이스 객체
    Signup *signupPage;             // 회원가입 양식 다이얼로그 객체
};

#endif // MAINWINDOW_H