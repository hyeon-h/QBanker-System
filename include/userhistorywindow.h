#ifndef USERHISTORYWINDOW_H
#define USERHISTORYWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "history.h"

namespace Ui {
class UserHistoryWindow;
}

// 사용자 전용 거래 내역 조회 및 필터링 화면
class UserHistoryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserHistoryWindow(QWidget *parent = nullptr);
    ~UserHistoryWindow();

private slots:
    void on_pushButton_clicked();   // OK 버튼
    void on_pushButton_2_clicked(); // Cancel 버튼
    void on_pushButton_3_clicked(); // 설정된 필터 조건(날짜/금액 등)으로 내역 검색

protected:
    void closeEvent(QCloseEvent *event) override; // 창 닫기 시 부모 위젯 재표출 처리

private:
    Ui::UserHistoryWindow *ui;      // 사용자 이력 화면 UI 인터페이스

    // 검색 옵션에 부합하는 본인의 거래 데이터 필터링
    void filterAndDisplay(const SearchCriteria& sc);

    // 테이블 위젯에 필터링된 이력 데이터를 한 행씩 추가
    void addTableRow(const History& h);

    // 각 거래 데이터를 메세지로그로 변환
    QString getUserMessage(const History& h);
};

#endif // USERHISTORYWINDOW_H
