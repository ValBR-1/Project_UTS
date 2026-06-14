    #include "IzinAkses.h"
    #include <iostream>

    IzinAkses::IzinAkses() {
    //Inisialisasi awal untuk list kosong tanpa node
        daftarAturan = nullptr;
    }

    //Destruktor untuk membersihkan memori yang digunakan oleh linked list
    IzinAkses::~IzinAkses() {
        NodeAkses* current = daftarAturan;
        while (current != nullptr) {
            NodeAkses* temp = current;
            current = current->next;
            delete temp;
        }
    }

    //Fungsi insert untuk menyisipkan aturan akses baru ke barisan paling depan linked list
    void IzinAkses::daftarkanHakAkses(const std::string& User, const std::string& folder) {
        NodeAkses* current = daftarAturan;
        while (current != nullptr) {
            if (current->namaUser == User && current->folderIzin == folder) {
                return;
            }
            current = current->next;
        }

        NodeAkses* newNode = new NodeAkses;
        newNode->namaUser = User;
        newNode->folderIzin = folder;
        newNode->next = daftarAturan;
        daftarAturan = newNode;
    }

    //fungsi untuk validasi akses user dengan melakukan pencarian linear pada linked list
    bool IzinAkses::validasiAksesUser(const std::string& User, const std::string& folder) {
        NodeAkses* current = daftarAturan;
        while (current != nullptr) {
            if (current->namaUser == User && current->folderIzin == folder) {
                return true; 
            }
            current = current->next;
        }
        return false; 
    }

    void IzinAkses::cetakDaftarAkses() const {
        std::cout << "\n[DAFTAR HAK AKSES]:\n";
        NodeAkses* current = daftarAturan;
        while (current != nullptr) {
            std::cout << " -> User: " << current->namaUser << " | Folder: " << current->folderIzin << "\n";
            current = current->next;
        }
    }