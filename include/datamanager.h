#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QVector>
#include "history.h"

class DataManager
{
public:
    static DataManager& instance()
    {
        static DataManager inst; // 처음만 초기화되고, 이후에는 다시 호출해도 무시함.
        return inst; // 따라서 한가지 객체만을 return함.
    }
    QVector<History> hists;
    QString loginId;

    void loadJson();
    void saveJson();

private:
    DataManager(){}
};

#endif // DATAMANAGER_H
