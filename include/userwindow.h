#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include "senddialog.h"
#include "userhistorywindow.h"

namespace Ui {
class UserWindow;
}

// 사용자 메인 화면: 잔액 조회, 송금 창 호출 및 이력 화면 접근 관리
class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent = nullptr);
    ~UserWindow();

private slots:
    void on_pushButton_clicked();   // 송금 다이얼로그(SendDialog) 실행
    void on_pushButton_2_clicked(); // 개인 거래 이력 창(UserHistoryWindow) 호출
    void on_pushButton_3_clicked(); // 로그아웃 및 초기 화면으로 복귀

private:
    SendDialog* sendDialog;                 // 송금 처리를 위한 다이얼로그 객체
    UserHistoryWindow* userHistoryWindow;   // 개인 거래 내역 표시용 윈도우 객체
    Ui::UserWindow *ui;                     // 사용자 화면 UI 인터페이스 객체

public:
    // 로그인 시 전달받은 사용자 이름과 잔액을 화면에 초기 설정
    void setUserInfo(QString name, QString balance);

    // XML 파일로부터 최신 사용자 정보를 다시 읽어와 화면(Label 등) 갱신
    void refreshUserInfo();

protected:
    // 창이 화면에 나타날 때마다 최신 데이터로 새로고침 수행
    void showEvent(QShowEvent *event) override;
};

#endif // UserWindow_H
