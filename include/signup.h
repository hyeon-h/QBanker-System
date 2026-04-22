#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QString>

namespace Ui {
class Signup;
}

// 신규 사용자 등록 창: 계좌 생성 및 초기 데이터 저장 수행
class Signup : public QDialog
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

private slots:
    void on_buttonBox_accepted(); // 회원가입 승인: 유효성 검사 및 데이터 저장 실행

private:
    Ui::Signup *ui;               // 회원가입 화면 UI 인터페이스 객체

    // 입력된 ID의 중복 여부를 XML 데이터에서 확인
    bool isIdDuplicated(QString id);

    // 신규 사용자 정보(ID, PW, 초기 입금액)를 XML 파일에 노드로 추가
    void saveToXml(QString id, QString pw, int deposit);
};

#endif