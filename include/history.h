#ifndef HISTORY_H
#define HISTORY_H
#include <QString>
#include <QDateTime>

enum class ActionType {
    Transfer,
    CreateAccount,
    Delete
};

struct History
{
    QDateTime dateTime;
    QString from; // 송신자 or 가입자
    QString to; // 수신자
    ActionType action;
    int amount;

};

struct SearchCriteria { 
    // 날짜 필터 관련
    bool useDate;      // 날짜 필터 사용 여부 (체크박스 상태)
    QDate start;       // 검색 시작 날짜
    QDate end;         // 검색 종료 날짜

    // 금액 필터 관련
    bool useAmount;    // 금액 필터 사용 여부
    int minAmount;     // 최소 금액 범위
    int maxAmount;     // 최대 금액 범위

    // 사용자 및 유형 필터 관련
    bool useUser;      // 특정 사용자 검색 여부 (필요시 사용)
    QString userName;  // 검색할 사용자 이름
    int typeIndex;     // 거래 유형 선택 (0: 전체, 1: 송신, 2: 수신)
};

#endif // HISTORY_H
