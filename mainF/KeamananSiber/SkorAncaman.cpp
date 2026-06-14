#include "SkorAncaman.h"
#include <iostream>

// Konstruktor awal untuk menyatakan BST ancaman masih kosong.
SkorAncaman::SkorAncaman() {
    root = nullptr;
}

// Destructor untuk membersihkan seluruh node BST saat objek dihapus.
SkorAncaman::~SkorAncaman() {
    deleteTree(root);
}

// Fungsi rekursif untuk menghapus semua node BST secara aman.
void SkorAncaman::deleteTree(NodeTree* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

// Fungsi untuk mencari node dengan skor ancaman tertinggi.
NodeTree* SkorAncaman::findMax(NodeTree* node) const {
    if (node == nullptr) {
        return nullptr;
    }

    NodeTree* current = node;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current;
}

// Fungsi untuk menyisipkan data user dan skor ancaman ke dalam BST.
NodeTree* SkorAncaman::insertNode(NodeTree* node, const std::string User, int skor) {
    if (node == nullptr) {
        NodeTree* newNode = new NodeTree;
        newNode->namaUser = User;
        newNode->totalSkorKritis = skor;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    if (skor < node->totalSkorKritis) {
        node->left = insertNode(node->left, User, skor);
    } else {
        node->right = insertNode(node->right, User, skor);
    }

    return node;
}

// Fungsi publik untuk menerima input skor ancaman dari user.
void SkorAncaman::inputSkorAncaman(const std::string User, int skor) {
    root = insertNode(root, User, skor);
}

// Fungsi untuk menampilkan urutan ancaman dalam traversal in-order.
void SkorAncaman::cetakUrutanBahaya() const {
    inOrderTraversal(root);
}

// Fungsi traversal untuk menampilkan data BST dari kecil ke besar.
void SkorAncaman::inOrderTraversal(NodeTree* node) const {
    if (node != nullptr) {
        inOrderTraversal(node->left);
        std::cout << "- " << node->namaUser
                  << " | Skor Ancaman: " << node->totalSkorKritis << std::endl;
        inOrderTraversal(node->right);
    }
}

// Fungsi untuk menampilkan ancaman dengan skor paling tinggi.
void SkorAncaman::deteksiAncamanTertinggi() const {
    NodeTree* maxNode = findMax(root);
    if (maxNode == nullptr) {
        std::cout << "Belum ada data ancaman yang masuk." << std::endl;
        return;
    }

    std::cout << "Ancaman tertinggi saat ini: " << maxNode->namaUser
              << " dengan skor " << maxNode->totalSkorKritis << std::endl;
}