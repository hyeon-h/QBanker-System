#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include "adminhistorywindow.h"
#include "meminfodialog.h"

namespace Ui {
class AdminWindow;
}

// 관리자 메인 화면: 회원 정보 관리 및 전체 이력 조회 접근 제어
class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);
    ~AdminWindow();

private slots:
    void on_pushButton_clicked();   // 전체 회원 정보 관리 창(Dialog) 호출
    void on_pushButton_2_clicked(); // 전체 거래 이력 조회 화면(Window) 호출

private:
    AdminHistoryWindow* adminHistoryWindow; // 전체 거래 내역 확인용 윈도우 객체
    MemInfoDialog* memInfoDialog;           // 회원 정보 수정/삭제용 다이얼로그 객체
    Ui::AdminWindow *ui;                    // 관리자 화면 UI 인터페이스
};

#endif // ADMINWINDOW_H
