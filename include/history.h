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
    bool useDate;
    QDate start;
    QDate end;

    bool useAmount;
    int minAmount;
    int maxAmount;

    bool useUser;
    QString userName;
    int typeIndex; // 0: 전체, 1: 송신, 2: 수신
};

#endif // HISTORY_H
