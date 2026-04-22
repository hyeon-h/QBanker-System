#ifndef SENDDIALOG_H
#define SENDDIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include <QTimer>
#include "history.h"
#include "datamanager.h"

namespace Ui {
class SendDialog;
}

// 송금 실행 창: 사용자 간 금액 이체 및 거래 데이터 기록 수행
class SendDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SendDialog(QWidget *parent = nullptr);
    ~SendDialog();
    
    void clearInputs();                 // 입력 필드(금액, 수신자 등) 초기화

private slots:
    void on_pushButton_clicked();       // 송금 실행: 잔액 검증, XML 업데이트 및 JSON 이력 생성
    void on_pushButton_2_clicked();     // 취소: 송금 중단 및 창 닫기

protected:
    void closeEvent(QCloseEvent *event) override; // 창 닫기 시 부모 화면 상태 관리

private:
    Ui::SendDialog *ui;                 // 송금 화면 UI 인터페이스 객체
    QString senderName;                 // 송신자(현재 로그인 유저) 이름 저장 변수

public:
    // 부모 창으로부터 송신자 정보를 전달받아 설정
    void setSenderInfo(QString name);
};

#endif
