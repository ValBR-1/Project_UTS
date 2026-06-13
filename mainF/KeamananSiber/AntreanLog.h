#ifndef ANTREANLOG_H
#define ANTREANLOG_H
#include "../modelSistem.h"


class AntreanLog {
private:
    
    struct NodeAntrean {
        CatatanAktivitas data;
        NodeAntrean* next;
    };

    NodeAntrean* head;
    NodeAntrean* tail;
    int totalAntrean;

public:
    AntreanLog();
    ~AntreanLog();

    void masukkanLog(CatatanAktivitas dataBaru);
    CatatanAktivitas ambilLog();
    bool isEmpty() const;
    int getTotalAntrean() const;

};

#endif