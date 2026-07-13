#ifndef MODELSISTEM_H
#define MODELSISTEM_H

#include <string>

// Struktur untuk menyimpan satu catatan aktivitas pengguna dalam sistem keamanan.
struct CatatanAktivitas {
    std::string namaUser;
    std::string tindakan;
    std::string namaFile;
    int bobotBahaya;
};

// Struktur node untuk daftar izin akses yang tersimpan dalam linked list.
struct  NodeAkses{
    std::string namaUser;
    std::string folderIzin;
    NodeAkses* next;
};

// Struktur node untuk menyimpan data backup file yang akan dipulihkan.
struct NodeCadangan{
    std::string namaFile;
    std::string isiTeksAsli;
    NodeCadangan* next;
};

// Struktur node untuk menyimpan data skor ancaman dalam BST.
struct NodeTree{
    std::string namaUser;
    int totalSkorKritis;
    NodeTree* left;
    NodeTree* right;
};

// Struktur untuk merepresentasikan koneksi antar perangkat dalam jaringan.
struct connection{
    int destId;
    connection* next;
};

// Struktur untuk merepresentasikan perangkat dalam jaringan.
struct device{
    std::string namaDevice;
    std::string tipeDevice;
    int vulnScore;
    connection* connHead;
};

#endif