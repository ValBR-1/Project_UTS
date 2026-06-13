#ifndef CADANGANFILE_H
#define CADANGANFILE_H

#include "../modelSistem.h"
#include <string>

class CadanganFile {
    private:
        NodeCadangan* top;  
    public:
        CadanganFile();
        ~CadanganFile();
        void pushBackup(const std::string File,std::string TeksAsli);
        NodeCadangan* popBackup();
        bool isEmpty() const;
        void cetakCadangan() const;
};
#endif