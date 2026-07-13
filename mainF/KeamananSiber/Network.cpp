#include "Network.h"
#include <iostream>

//Fungsi untuk menginisialisasi jaringan dan perangkatnya
Network::Network(){
    devCount = 0;
    for(int i = 0; i < MAX_DEV; i++){
        devices[i].connHead = nullptr;
    }
}

//Fungsi untuk membersihkan memori yang digunakan oleh koneksi perangkat
Network::~Network(){
    for(int i = 0; i < devCount; i++){
        connection* current = devices[i].connHead;
        while(current != nullptr){
            connection* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

//Fungsi untuk menambahkan perangkat baru ke jaringan
void Network::addDevice(std::string namaDevice, std::string tipeDevice, int vuln){
    if (devCount < MAX_DEV){
        devices[devCount].namaDevice = namaDevice;
        devices[devCount].tipeDevice = tipeDevice;
        devices[devCount].vulnScore = vuln;
        devices[devCount].connHead = nullptr;
        devCount++;
    }
}

//Fungsi untuk menambahkan koneksi antara dua perangkat dalam jaringan
void Network::addLink(int srcId, int destId){
    if(srcId >= devCount || destId >= devCount || srcId == destId) return;

    connection* newconn = new connection;
    newconn->destId = destId;
    newconn->next = devices[srcId].connHead;
    devices[srcId].connHead = newconn;
}

//Fungsi untuk menampilkan topologi jaringan dan koneksi antar perangkat
void Network::printTopology() const{
    std::cout << "\n[TOPOLOGI JARINGAN AKTIF]:\n";
    for(int i = 0;i < devCount; i++){
        std::cout << " [" << i << "] " << devices[i].namaDevice << " (" << devices[i].tipeDevice << ") -> Koneksi :";
        connection* temp = devices[i].connHead;
        while(temp != nullptr){
            std::cout << devices[temp->destId].namaDevice << ", ";
            temp = temp->next;
        }
        std::cout << "nullptr\n";
    }
}

//Fungsi untuk melakukan pemindaian penyebaran ancaman dari perangkat tertentu
void Network::scanSpread(int startId){
    if (startId >= devCount || startId < 0) return;
    std::cout << "\n[SCAN] Radius penyebaran infeksi jaringan (Mulai : " << devices[startId].namaDevice <<"):\n";

    bool* visited = new bool[devCount]{false};
    int* queue = new int[devCount];
    int front = 0, rear = 0;

    visited[startId] = true;
    queue[rear++] = startId;

    while (front < rear){
        int curr = queue[front++];
        std::cout << " -> Bahaya Kontaminasi : " << devices[curr].namaDevice << "\n";
    

    connection* temp = devices[curr].connHead;
    while(temp != nullptr){
        if (!visited[temp->destId]){
            visited[temp->destId] = true;
            queue[rear++] = temp->destId;
        }
        temp = temp->next;
        }
    }
    delete[] visited; delete[] queue;
}

//Fungsi rekursif untuk menelusuri jalur infiltrasi ancaman dalam jaringan
void Network::traceRec(int currId, bool visited[]){
    visited[currId]= true;
    std::cout << " -> " << devices[currId].namaDevice;

    connection* temp = devices[currId].connHead;
    while(temp != nullptr){
        if(!visited[temp->destId]){
            traceRec(temp->destId, visited);
        }
        temp = temp->next;
    }
}

//Fungsi untuk menelusuri jalur infiltrasi ancaman dari perangkat tertentu
void Network::traceBreach(int startId){
    if(startId >= devCount || startId < 0) return;
    std::cout << "\n[TRACE] Jalur ifiltrasi ancaman terdalam :\n  Rute : ";
    bool* visited = new bool[devCount]{false};
    traceRec(startId, visited);
    std::cout << " -> Selesai\n";
    delete[] visited;
}

//Fungsi untuk melakukan audit terhadap perangkat tertentu dalam jaringan
void Network::auditDevice(std::string target){
    std::cout << "\n[AUDIT] Memeriksa integritas perangkat...\n";
    bool found = false;

    for(int i = 0; i < devCount; i++){
        if(devices[i].namaDevice == target){
            std::cout << " [INFO] Data ditemukan:\n";
            std::cout << " - Nama perangkat : " << devices[i].namaDevice << "\n";
            std::cout << " - Tipe perangkat : " << devices[i].tipeDevice << "\n";
            std::cout << " - Risiko kerentanan : " << devices[i].vulnScore << "/100\n";
            found = true; break;
        }
    }
    if(!found) std::cout << " [PERINGATAN] Perangkat \"" << target << "\" Tidak dikenali!\n";
}

//Fungsi untuk mengurutkan perangkat berdasarkan skor risiko kerentanan tertinggi
void Network::prioritizeIsolation(){
    std::cout << "\n[URUTKAN] Prioritas isolasi darurat perangkat (Skor risiko tertinggi) : \n";

    device temp[MAX_DEV];
    for(int i =0; i < devCount; i++) temp[i] = devices[i];
    for (int i = 0; i < devCount - 1; i++){
        int maxIdx = i;
        for (int j = i + 1; j < devCount; j++){
            if(temp[j].vulnScore > temp[maxIdx].vulnScore) maxIdx = j;
        }
        device swap = temp[i];
        temp[i] = temp[maxIdx];
        temp[maxIdx] = swap;
    }

    for (int i = 0; i < devCount; i++){
        std::cout << " Prioritas [" << i+1 << "] -> " << temp[i].namaDevice
                  << " (" << temp[i].vulnScore << "/100)\n";
    }
}