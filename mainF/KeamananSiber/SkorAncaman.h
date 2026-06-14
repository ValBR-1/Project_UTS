#ifndef SKORANCAMAN_H
#define SKORANCAMAN_H

#include <string>
#include "../modelSistem.h"

// Class untuk menyimpan dan menganalisis skor ancaman menggunakan BST.
class SkorAncaman {
private:
   NodeTree* root;

//Fungsi rekursif untuk menghapus seluruh node pada tree saat destruktor dipanggil
    NodeTree* insertNode(NodeTree* node, const std::string User, int skor);
    void inOrderTraversal(NodeTree* node) const;
    void deleteTree(NodeTree* node);
    NodeTree* findMax(NodeTree* node) const;
public:
    SkorAncaman();
    ~SkorAncaman();
    void inputSkorAncaman(const std::string User, int skor);
    void cetakUrutanBahaya() const;
    void deteksiAncamanTertinggi() const;
};

#endif