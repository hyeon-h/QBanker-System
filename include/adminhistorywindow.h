#ifndef ADMINHISTORYWINDOW_H
#define ADMINHISTORYWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "history.h"

namespace Ui {
class AdminHistoryWindow;
}

// 관리자용 전체 거래 내역 조회 및 필터링 창
class AdminHistoryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminHistoryWindow(QWidget *parent = nullptr);
    ~AdminHistoryWindow();

private slots:
    void on_pushButton_clicked();   // OK 버튼
    void on_pushButton_2_clicked(); // Cancel 버튼
    void on_pushButton_3_clicked(); // 검색 조건(날짜/유형 등)에 맞는 내역 조회

protected:
    void closeEvent(QCloseEvent *event) override; // 종료 시 메인 화면 복귀 처리

private:
    Ui::AdminHistoryWindow *ui;     // UI 인터페이스 관리 객체

    // 거래 내역 데이터를 화면용 메시지 문자열로 변환
    QString getHistoryMessage(const History& h);

    // 검색 기준(SearchCriteria)에 따라 JSON 데이터를 필터링해서 표시
    void filterAndDisplay(const SearchCriteria& sc);

    // 테이블 위젯에 데이터 한 행 추가
    void addTableRow(const History& h);
};

#endif // ADMINHISTORYWINDOW_H
