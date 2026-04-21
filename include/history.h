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

#endif // HISTORY_H
