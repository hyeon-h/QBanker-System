#ifndef MEMINFODIALOG_H
#define MEMINFODIALOG_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class MemInfoDialog;
}

// 관리자용 회원 정보 관리창: 전체 사용자 목록 열람 및 활성화/ 비활성화 수행
class MemInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MemInfoDialog(QWidget *parent = nullptr);
    ~MemInfoDialog();

private slots:
    void on_pushButton_clicked();   // OK 버튼
    void on_pushButton_2_clicked(); // Cancel 버튼
    void on_pushButton_3_clicked(); // 선택된 사용자 정보 수정 내용 저장(활성화/비활성화)

private:
    void closeEvent(QCloseEvent *event) override; // 닫기 이벤트 발생 시 부모 창 갱신 처리
    void loadUserData();                          // XML/JSON에서 전체 회원 데이터를 읽어와 리스트업

    Ui::MemInfoDialog *ui;                        // 회원 관리 UI 인터페이스 객체
};

#endif // MEMINFODIALOG_H
