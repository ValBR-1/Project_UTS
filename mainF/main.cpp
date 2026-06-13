#include <iostream>
#include <limits>
#include <string>
#include "modelSistem.h"
#include "KeamananSiber/AntreanLog.h"
#include "KeamananSiber/BerkasUmpan.h"
#include "KeamananSiber/IzinAkses.h"
#include "KeamananSiber/CadanganFile.h"
#include "KeamananSiber/SkorAncaman.h"

using namespace std;

int main() {
    AntreanLog antreanTrafic;
    BerkasUmpan detectorHoneypot;
    IzinAkses firewallACL;
    CadanganFile stackSnapshot;
    SkorAncaman bstAnalsytic;

    firewallACL.daftarkanHakAkses("Jamal", "Folder_Riset");
    firewallACL.daftarkanHakAkses("Udin", "Folder_Slide");
    firewallACL.daftarkanHakAkses("Asep", "Folder_Video");

    int pilihanMenu = -1;

    do {
        cout << "\n=== Sistem Keamanan Siber ===" << endl;
        cout << "1. Catat Aktivitas Pengguna" << endl;
        cout << "2. Tampilkan Log Aktivitas" << endl;
        cout << "3. Deteksi Honeypot" << endl;
        cout << "4. Kelola Izin Akses" << endl;
        cout << "5. Kelola Cadangan File" << endl;
        cout << "6. Analisis Skor Ancaman" << endl;
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
                cin >> aktivitas.bobotBahaya;

                if (cin.fail() || aktivitas.bobotBahaya < 0 || aktivitas.bobotBahaya > 10) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Bobot bahaya harus berada dalam rentang 0-10." << endl;
                    break;
                }

                antreanTrafic.masukkanLog(aktivitas);
                cout << "Log aktivitas berhasil dicatat." << endl;
                break;
            }
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
                }
                break;
            }
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
            case 4: {
                int subPilihan;
                cout << "\n[Kelola Izin Akses]" << endl;
                cout << "1. Tambah hak akses" << endl;
                cout << "2. Tampilkan daftar izin" << endl;
                cout << "3. Validasi akses" << endl;
                cout << "Pilih sub menu: ";
                cin >> subPilihan;

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
            case 5: {
                int subPilihan;
                cout << "\n[Kelola Cadangan File]" << endl;
                cout << "1. Simpan backup" << endl;
                cout << "2. Tampilkan backup" << endl;
                cout << "3. Pulihkan backup teratas" << endl;
                cout << "Pilih sub menu: ";
                cin >> subPilihan;

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
            case 6: {
                string user;
                int skor;
                cout << "Nama pengguna: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, user);
                cout << "Skor ancaman: ";
                cin >> skor;
                bstAnalsytic.inputSkorAncaman(user, skor);
                cout << "Skor ancaman berhasil ditambahkan." << endl;
                cout << "\nUrutan ancaman dari yang paling aman ke paling berbahaya:" << endl;
                bstAnalsytic.cetakUrutanBahaya();
                bstAnalsytic.deteksiAncamanTertinggi();
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