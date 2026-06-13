#ifndef CADANGANFILE_H
#define CADANGANFILE_H

#include "../modelSistem.h"
#include <string>

class CadanganFile {
    private:
        NodeCadangan* top;
        static const int MAX_BACKUP = 50;

    public:
        CadanganFile();
        ~CadanganFile();
        void pushBackup(const std::string File, std::string TeksAsli);
        NodeCadangan* popBackup();
        bool isEmpty() const;
        bool isFull() const;
        void cetakCadangan() const;
};
#endif