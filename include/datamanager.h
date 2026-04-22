#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "history.h"
#include <QVector>
#include <QString>

// 프로그램 전역 데이터 관리 및 JSON I/O 제어 클래스 (Singleton)
class DataManager
{
public:
    // 싱글톤 인스턴스 반환: 전역 어디서든 동일한 데이터 객체에 접근 가능
    static DataManager& instance() {
        static DataManager inst; // 정적 객체로 단 한 번만 초기화
        return inst;
    }

    QVector<History> hists;   // 로드된 전체 거래 내역 리스트
    QString loginId;          // 세션 유지를 위한 현재 로그인 사용자 ID
    QString path;             // 데이터 저장 및 불러오기에 사용되는 JSON 파일 경로

    void addHistory(const History& h); // 신규 거래 내역 추가 후 saveJson 자동 호출
    void loadJson();                   // 지정된 경로(path)에서 JSON 데이터를 파싱하여 hists에 로드
    void saveJson();                   // 현재 hists 리스트의 데이터를 JSON 형식으로 파일에 저장

private:
    DataManager(); // 외부 생성 방지 (싱글톤 패턴 엄수)
};

#endif // DATAMANAGER_H
