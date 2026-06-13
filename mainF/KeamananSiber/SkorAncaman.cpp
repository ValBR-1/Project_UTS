#include "SkorAncaman.h"
#include <iostream>

SkorAncaman::SkorAncaman() {
    root = nullptr;
}

SkorAncaman::~SkorAncaman() {
    deleteTree(root);
}

void SkorAncaman::deleteTree(NodeTree* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

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

void SkorAncaman::inputSkorAncaman(const std::string User, int skor) {
    root = insertNode(root, User, skor);
}

void SkorAncaman::cetakUrutanBahaya() const {
    inOrderTraversal(root);
}

void SkorAncaman::inOrderTraversal(NodeTree* node) const {
    if (node != nullptr) {
        inOrderTraversal(node->left);
        std::cout << "- " << node->namaUser
                  << " | Skor Ancaman: " << node->totalSkorKritis << std::endl;
        inOrderTraversal(node->right);
    }
}

void SkorAncaman::deteksiAncamanTertinggi() const {
    NodeTree* maxNode = findMax(root);
    if (maxNode == nullptr) {
        std::cout << "Belum ada data ancaman yang masuk." << std::endl;
        return;
    }

    std::cout << "Ancaman tertinggi saat ini: " << maxNode->namaUser
              << " dengan skor " << maxNode->totalSkorKritis << std::endl;
}