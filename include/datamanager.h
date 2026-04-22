#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "history.h"
#include <QVector>
#include <QString>

class DataManager
{
public:
    // 싱글톤 인스턴스 반환 (전체 공유 객체)
    static DataManager& instance() {
        static DataManager inst; // 최초 호출 시에만 초기화
        return inst;
    }

    QVector<History> hists;   // 거래 내역 전체 리스트
    QString loginId;          // 현재 로그인된 사용자 ID
    QString path;             // 데이터 저장용 JSON 파일 경로

    void addHistory(const History& h); // 새로운 거래 내역 추가 및 파일 저장
    void loadJson();                   // JSON 파일로부터 데이터 불러오기
    void saveJson();                   // 현재 데이터를 JSON 파일로 저장

private:
    DataManager(); // 외부에서 객체 생성을 못 하도록 차단
};

#endif // DATAMANAGER_H
