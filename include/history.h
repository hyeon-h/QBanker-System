#ifndef HISTORY_H
#define HISTORY_H
#include <QString>
#include <QDateTime>

// 거래 및 시스템 활동 기록의 유형
enum class ActionType {
    Transfer,       // 송금
    CreateAccount,  // 계좌 생성(회원가입)
    Delete          // 계정 삭제
};

// 단일 거래 이력 정보를 담는 구조체
struct History
{
    QDateTime dateTime; // 거래 발생 일시
    QString from;       // 송신자 또는 활동 주체(가입자)
    QString to;         // 수신자 (송금 시 사용)
    ActionType action;  // 활동 유형 (송금/가입/삭제)
    int amount;         // 거래 금액
};

// 이력 검색 및 필터링을 위한 기준 데이터 구조체
struct SearchCriteria { 
    // 날짜 필터 관련
    bool useDate;       // 날짜 필터 활성화 여부
    QDate start;        // 검색 시작 범위 날짜
    QDate end;          // 검색 종료 범위 날짜

    // 금액 필터 관련
    bool useAmount;     // 금액 필터 활성화 여부
    int minAmount;      // 검색 최소 금액
    int maxAmount;      // 검색 최대 금액

    // 사용자 및 유형 필터 관련
    bool useUser;       // 특정 사용자 검색 활성화 여부
    QString userName;   // 대상 사용자 식별자(ID)
    int typeIndex;      // 콤보박스 선택 인덱스 (0:전체, 1:송신, 2:수신 등)
};

#endif // HISTORY_H
