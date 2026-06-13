#ifndef MODELSISTEM_H
#define MODELSISTEM_H

#include <string>

struct CatatanAktivitas {
    std::string namaUser;
    std::string tindakan;
    std::string namaFile;
    int bobotBahaya;
};

struct  NodeAkses{
    std::string namaUser;
    std::string folderIzin;
    NodeAkses* next;
};

struct NodeCadangan{
    std::string namaFile;
    std::string isiTeksAsli;
    NodeCadangan* next;
};

struct NodeTree{
    std::string namaUser;
    int totalSkorKritis;
    NodeTree* left;
    NodeTree* right;
};

#endif