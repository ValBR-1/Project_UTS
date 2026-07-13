#ifndef NETWORK_H
#define NETWORK_H

#include "../modelSistem.h"
#include <string>

// Struktur data untuk merepresentasikan koneksi antar perangkat dalam jaringan
class Network{
    private:
        static const int MAX_DEV = 6;
        device devices[MAX_DEV];
        int devCount;
    void traceRec(int currId, bool visited[]);

    public:
        Network();
        ~Network();

        void addDevice(std::string namaDevice, std::string tipeDevice, int vuln);
        void addLink(int srcId, int destId);
        void printTopology() const;

        //Fungsi untuk melakukan pemindaian penyebaran ancaman dari perangkat tertentu
        void scanSpread(int startId);
        void traceBreach(int startId);
        void auditDevice(std::string target);
        void prioritizeIsolation();
};

#endif