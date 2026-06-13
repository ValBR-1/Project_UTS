#include "AntreanLog.h"
#include <stdexcept>

// Konstruktor: Kondisi awal saat sistem proteksi dijalankan
AntreanLog::AntreanLog() {
    head = nullptr;
    tail = nullptr;
    totalAntrean = 0;
}

// Destruktor: Membersihkan memori yang digunakan oleh antrean supaya memory tidak leak
AntreanLog::~AntreanLog() {
    while (!isEmpty()) {
        ambilLog();
    }
}

bool AntreanLog::isEmpty() const {
    return head == nullptr;
}

int AntreanLog::getTotalAntrean() const {
    return totalAntrean;
}

//Fungsi memasukkan Log baru dari belakang antrean
void AntreanLog::masukkanLog(CatatanAktivitas dataBaru) {
    NodeAntrean* newNode = new NodeAntrean;
    newNode->data = dataBaru;
    newNode->next = nullptr;

    if (isEmpty()) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    totalAntrean++;
}

//Fungsi queue untuk mengambil log dari depan antrean
    CatatanAktivitas AntreanLog::ambilLog() {
        if (isEmpty()) {
            throw std::runtime_error("Antrean log kosong, tidak ada log untuk diambil!");
        }

        NodeAntrean* temp = head;
        CatatanAktivitas dataKeluar = temp->data;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }

        delete temp;
        totalAntrean--;

        return dataKeluar;
}   