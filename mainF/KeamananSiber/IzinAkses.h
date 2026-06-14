#ifndef IZINAKSES_H
#define IZINAKSES_H

#include "../modelSistem.h"
#include <string>

// Class untuk mengelola daftar izin akses pengguna dengan linked list.
class IzinAkses {
private:
    NodeAkses* daftarAturan;

public:
    IzinAkses();
    ~IzinAkses();
    void daftarkanHakAkses(const std::string& User, const std::string& folder);
    bool validasiAksesUser(const std::string& User, const std::string& folder);
    void cetakDaftarAkses() const;
};
#endif