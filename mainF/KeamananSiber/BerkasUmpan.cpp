#include "BerkasUmpan.h"
#include <iostream>

// Konstruktor untuk menginisialisasi daftar file jebakan
BerkasUmpan::BerkasUmpan() {
    daftarFileJebakan[0] = "rekap_gaji_maret2026.xlsx";
    daftarFileJebakan[1] = "root_passwords.txt";
    daftarFileJebakan[2] = "master_database.sql";
    daftarFileJebakan[3] = "blueprints_proyek_rahasia.pdf";
}

//Fungsi loop untuk mencari data array
bool BerkasUmpan::periksaUmpan(const std::string& namaFileTarget) const {
    for (int i = 0; i < KAPASITAS_UMPAN; i++) {
        if (daftarFileJebakan[i] == namaFileTarget) {
            return true;
        }
    }
    return false;
}

// Fungsi untuk menampilkan seluruh file honeypot yang sedang dipantau.
void BerkasUmpan::cetakDaftarUmpan() const {
    std::cout << "\n[SISTEM] Monitoring File Jebakan aktif:\n";
    for (int i = 0; i < KAPASITAS_UMPAN; i++) {
        std::cout << " -> " << daftarFileJebakan[i] << "\n";
    }
}