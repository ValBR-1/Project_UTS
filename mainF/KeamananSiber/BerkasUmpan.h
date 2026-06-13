#ifndef BERKASUMPAN_H
#define BERKASUMPAN_H

#include "../modelSistem.h"
#include <string>

class BerkasUmpan {
private:
 // Kapasitas maksimum umpan
    static const int KAPASITAS_UMPAN = 4;
    std::string daftarFileJebakan[KAPASITAS_UMPAN];

public:
   BerkasUmpan();
   bool periksaUmpan(const std::string& namaFileTarget) const;
   void cetakDaftarUmpan() const;
};
#endif