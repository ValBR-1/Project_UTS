#include <iostream>
#include <limits>
#include <string>
#include "modelSistem.h"
#include "KeamananSiber/AntreanLog.h"
#include "KeamananSiber/BerkasUmpan.h"
#include "KeamananSiber/IzinAkses.h"
#include "KeamananSiber/CadanganFile.h"
#include "KeamananSiber/SkorAncaman.h"
#include "KeamananSiber/Network.h"

using namespace std;

bool validasiInputInt(int& nilai) {
    if (!(cin >> nilai)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

int main() {
    AntreanLog antreanTrafic;
    BerkasUmpan detectorHoneypot;
    IzinAkses firewallACL;
    CadanganFile stackSnapshot;
    SkorAncaman bstAnalsytic;
    Network net;

    // Data awal untuk simulasi sistem izin akses.
    firewallACL.daftarkanHakAkses("Jamal", "Folder_Riset");
    firewallACL.daftarkanHakAkses("Udin", "Folder_Slide");
    firewallACL.daftarkanHakAkses("Asep", "Folder_Video");

    // Data awal untuk simulasi jaringan perangkat.
    net.addDevice("Router Utama", "ROUTER", 15);
    net.addDevice("Server Pusat", "SERVER", 90);
    net.addDevice("PC Jamal", "PC_USER", 45);
    net.addDevice("PC Udin", "PC_USER", 65);
    net.addDevice("PC Asep", "PC_USER", 30);
    net.addDevice("Backup Cloud", "SERVER", 10);

    // Menambahkan koneksi antar perangkat dalam jaringan.
    net.addLink(0,2);
    net.addLink(0,3);
    net.addLink(0,4);
    net.addLink(2,1);
    net.addLink(3,1);
    net.addLink(1,5);

    int pilihanMenu = -1;

    // Menu utama sistem keamanan siber.
    do {
        cout << "\n=== Sistem Keamanan Siber ===" << endl;
        cout << "1. Catat Aktivitas Pengguna" << endl;
        cout << "2. Tampilkan Log Aktivitas" << endl;
        cout << "3. Deteksi Honeypot" << endl;
        cout << "4. Kelola Izin Akses" << endl;
        cout << "5. Kelola Cadangan File" << endl;
        cout << "6. Analisis Skor Ancaman" << endl;
        cout << "7. Audit & Respon Insiden Jaringan" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihanMenu;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Silakan masukkan angka menu." << endl;
            continue;
        }

        switch (pilihanMenu) {
            // Menangkap aktivitas pengguna dan menyimpannya ke antrean log.
            case 1: {
                CatatanAktivitas aktivitas;
                cout << "Nama pengguna: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, aktivitas.namaUser);
                cout << "Tindakan: ";
                getline(cin, aktivitas.tindakan);
                cout << "Nama file: ";
                getline(cin, aktivitas.namaFile);
                cout << "Bobot bahaya (0-10): ";
                if (!validasiInputInt(aktivitas.bobotBahaya)) {
                    cout << "Bobot bahaya harus berupa angka." << endl;
                    break;
                }

                if (aktivitas.bobotBahaya < 0 || aktivitas.bobotBahaya > 10) {
                    cout << "Bobot bahaya harus berada dalam rentang 0-10." << endl;
                    break;
                }

                antreanTrafic.masukkanLog(aktivitas);
                cout << "Log aktivitas berhasil dicatat." << endl;
                break;
            }
            // Menampilkan log aktivitas yang tersimpan dalam antrean.
            case 2: {
                if (antreanTrafic.isEmpty()) {
                    cout << "Belum ada log aktivitas." << endl;
                    break;
                }
                cout << "\n[LOG AKTIVITAS]" << endl;
                while (!antreanTrafic.isEmpty()) {
                    CatatanAktivitas log = antreanTrafic.ambilLog();
                    cout << "- User: " << log.namaUser
                         << " | Tindakan: " << log.tindakan
                         << " | File: " << log.namaFile
                         << " | Bahaya: " << log.bobotBahaya << endl;
                    bstAnalsytic.inputSkorAncaman(log.namaUser, log.bobotBahaya);
                }
                break;
            }
            // Memeriksa apakah file target termasuk dalam daftar honeypot.
            case 3: {
                string namaFile;
                cout << "Masukkan nama file yang akan diuji: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, namaFile);
                if (detectorHoneypot.periksaUmpan(namaFile)) {
                    cout << "Peringatan: file tersebut terdeteksi sebagai file jebakan (honeypot)." << endl;
                } else {
                    cout << "File aman. Tidak ditemukan dalam daftar honeypot." << endl;
                }
                detectorHoneypot.cetakDaftarUmpan();
                break;
            }
            // Mengelola hak akses pengguna melalui linked list.
            case 4: {
                int subPilihan;
                cout << "\n[Kelola Izin Akses]" << endl;
                cout << "1. Tambah hak akses" << endl;
                cout << "2. Tampilkan daftar izin" << endl;
                cout << "3. Validasi akses" << endl;
                cout << "Pilih sub menu: ";
                if (!validasiInputInt(subPilihan)) {
                    cout << "Input tidak valid. Silakan masukkan angka." << endl;
                    break;
                }

                if (subPilihan == 1) {
                    string user, folder;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Nama pengguna: ";
                    getline(cin, user);
                    cout << "Folder izin: ";
                    getline(cin, folder);
                    firewallACL.daftarkanHakAkses(user, folder);
                    cout << "Hak akses berhasil ditambahkan." << endl;
                } else if (subPilihan == 2) {
                    firewallACL.cetakDaftarAkses();
                } else if (subPilihan == 3) {
                    string user, folder;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Nama pengguna: ";
                    getline(cin, user);
                    cout << "Folder izin: ";
                    getline(cin, folder);
                    if (firewallACL.validasiAksesUser(user, folder)) {
                        cout << "Akses diizinkan." << endl;
                    } else {
                        cout << "Akses ditolak." << endl;
                    }
                } else {
                    cout << "Pilihan sub menu tidak valid." << endl;
                }
                break;
            }

            // Mengelola backup file dengan mekanisme stack LIFO.
            case 5: {
                int subPilihan;
                cout << "\n[Kelola Cadangan File]" << endl;
                cout << "1. Simpan backup" << endl;
                cout << "2. Tampilkan backup" << endl;
                cout << "3. Pulihkan backup teratas" << endl;
                cout << "Pilih sub menu: ";
                if (!validasiInputInt(subPilihan)) {
                    cout << "Input tidak valid. Silakan masukkan angka." << endl;
                    break;
                }

                if (subPilihan == 1) {
                    string namaFile, isiTeks;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Nama file: ";
                    getline(cin, namaFile);
                    cout << "Isi teks asli: ";
                    getline(cin, isiTeks);
                    try {
                        stackSnapshot.pushBackup(namaFile, isiTeks);
                        cout << "Backup berhasil disimpan." << endl;
                    } catch (const exception& e) {
                        cout << e.what() << endl;
                    }
                } else if (subPilihan == 2) {
                    stackSnapshot.cetakCadangan();
                } else if (subPilihan == 3) {
                    try {
                        NodeCadangan* backup = stackSnapshot.popBackup();
                        cout << "Backup dipulihkan: " << backup->namaFile << endl;
                        cout << "Isi teks asli: " << backup->isiTeksAsli << endl;
                        delete backup;
                    } catch (const exception& e) {
                        cout << e.what() << endl;
                    }
                } else {
                    cout << "Pilihan sub menu tidak valid." << endl;
                }
                break;
            }

            // Menerima skor ancaman dan menampilkan hasil analisis BST.
            case 6: {
                string user;
                int skor;
                cout << "Nama pengguna: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, user);
                cout << "Skor ancaman: ";
                if (!validasiInputInt(skor)) {
                    cout << "Input tidak valid. Skor ancaman harus berupa angka." << endl;
                    break;
                }
                bstAnalsytic.inputSkorAncaman(user, skor);
                cout << "Skor ancaman berhasil ditambahkan." << endl;
                cout << "\nUrutan ancaman dari yang paling aman ke paling berbahaya:" << endl;
                bstAnalsytic.cetakUrutanBahaya();
                bstAnalsytic.deteksiAncamanTertinggi();
                break;
            }

            // Menangani audit dan respon insiden jaringan.
            case 7: {
                int subPilihan;
                cout << "\n[Audit dan Respon Insiden Jaringan]" << endl;
                cout << "1. Tampilkan Topologi koneksi aktif" << endl;
                cout << "2. Scan radius dampak infeksi" << endl;
                cout << "3. Trace rute infiltrasi terobos" << endl;
                cout << "4. Audit detail log perangkat" << endl;
                cout << "5. Urutkan prioritas isolasi darurat" << endl;
                cout << "Pilih sub menu : ";
                if (!validasiInputInt(subPilihan)) {
                    cout << "Input tidak valid. Silakan masukkan angka." << endl;
                    break;
                }

                if (subPilihan == 1){
                    net.printTopology();
                }else if (subPilihan == 2){
                    int id;
                    cout << "Masukkan ID titik awal infeksi (0 - 5) : ";
                    if (!validasiInputInt(id)) {
                        cout << "Input tidak valid. ID harus berupa angka." << endl;
                        break;
                    }
                    net.scanSpread(id);
                }else if (subPilihan == 3){
                    int id;
                    cout << "Masukkan ID pintu masuk ancaman (0 - 5) : ";
                    if (!validasiInputInt(id)) {
                        cout << "Input tidak valid. ID harus berupa angka." << endl;
                        break;
                    }
                    net.traceBreach(id);
                }else if(subPilihan == 4){
                    string targetName;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Nama perangkat yang di audit : ";
                    getline(cin, targetName);
                    net.auditDevice(targetName);
                }else if (subPilihan == 5){
                    net.prioritizeIsolation();
                }else{
                    cout << "Pilihan menu tidak valid" << endl;
                }
                break;
            }
            case 0:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihanMenu != 0);

    return 0;
}