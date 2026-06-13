#include "CadanganFile.h"
#include <iostream>
#include <stdexcept>

CadanganFile::CadanganFile() {
//Kondisi awal saat sistem proteksi dijalankan, stack kosong tanpa node
    top = nullptr; 
}

CadanganFile::~CadanganFile() {
    while (!isEmpty()) {
        NodeCadangan* backup = popBackup();
        delete backup;
    }
}

bool CadanganFile::isEmpty() const {
    return top == nullptr;
}

//Fungsi push untuk menambahkan backup file baru ke atas stack LIFO
void CadanganFile::pushBackup(const std::string File, std::string TeksAsli) {
    NodeCadangan* newNode = new NodeCadangan;
    newNode->namaFile = File;
    newNode->isiTeksAsli = TeksAsli;
    newNode->next = top;
    top = newNode;
}

//Fungsi pop untuk mengambil backup file dari atas untuk fitur pemulihan darurat
NodeCadangan* CadanganFile::popBackup() {
    if (isEmpty()) {
        throw std::runtime_error("Stack cadangan kosong, tidak ada backup untuk dipulihkan!");
    }

    NodeCadangan* temp = top;
    top = top->next;
    return temp; 
}

void CadanganFile::cetakCadangan() const {
    std::cout << "\n[DAFTAR CADANGAN FILE]:\n";
    NodeCadangan* current = top;
    while (current != nullptr) {
        std::cout << " -> File: " << current->namaFile << " | Data Asli: " << current->isiTeksAsli << "\n";
        current = current->next;
    }
}