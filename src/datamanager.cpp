#include "datamanager.h"
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QApplication>

DataManager::DataManager()
{
    path = qApp->applicationDirPath() + "/../../../QBankerSystem";
    QDir().mkpath(path+ "/data");
}

void DataManager::addHistory(const History& h){
    // loadJson();
    hists.push_back(h);// 2.vector에 추가
    saveJson();
}

void DataManager::saveJson(){
    QJsonArray array; //3. jsonArray에 추가 (여기부터 저장)
    for(const History &h : std::as_const(hists))// const User& u : s를 읽기전용으로 받음
    {                                           // std::as_const(hists): hists 컨테이너 자체를 읽기 전용으로 만듬.
        QJsonObject obj;
        obj["dateTime"] = h.dateTime.toString(Qt::ISODate);//ISO Date 규격으로 변환한 문자열을 저장
        obj["from"] = h.from;
        obj["amount"] = h.amount;
        obj["action"] = static_cast<int>(h.action);// enum class를 저장하려면 정수변환 후 저장해야함.
        obj["to"] = h.to;
        array.append(obj);
    }

    QJsonDocument doc(array); //4.jsondoc 생성 및 파일 write
    QString fileName = path + "/data/history.json";
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly)) return;
    file.write(doc.toJson());
    file.close();
}

void DataManager::loadJson(){
    QString fileName = path + "/data/history.json"; // file open
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly)) return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll()); //json to doc
    file.close();

    hists.clear();

    QJsonArray array = doc.array(); // doc to array
    for(const QJsonValue& v: std::as_const(array))
    {
        QJsonObject obj = v.toObject();
        History hist;
        hist.dateTime = QDateTime::fromString((obj["dateTime"].toString()),Qt::ISODate);
        hist.from = obj["from"].toString();
        hist.amount = obj["amount"].toVariant().toInt();
        hist.action = static_cast<ActionType>(obj["action"].toInt());
        hist.to = obj["to"].toString();
        hists.push_back(hist);
    }

    for(const History& h : std::as_const(hists))
    {
        qDebug()<<h.dateTime.toString("yyyy-MM-dd HH:mm:ss")<<h.from<<h.amount << static_cast<int>(h.action) <<h.to;
    }
}