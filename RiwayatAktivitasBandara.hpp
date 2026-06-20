#ifndef RIWAYAT_AKTIVITAS_BANDARA_HPP
#define RIWAYAT_AKTIVITAS_BANDARA_HPP

#include <iostream>
#include <string>
#include <stack>
using namespace std;

struct Aktivitas {
    string keterangan;
};

stack<Aktivitas> riwayat;

void tambahAktivitas(string keterangan) {
    Aktivitas a;
    a.keterangan = keterangan;
    riwayat.push(a);
}

void hapusAktivitas() {
    if (!riwayat.empty()) {
        cout << "\n[UNDO] Aktivitas dibatalkan: \"" << riwayat.top().keterangan << "\"\n";
        riwayat.pop();
    } else {
        cout << "\n[INFO] Riwayat aktivitas kosong, tidak ada yang di-undo.\n";
    }
}

void lihatAktivitas() {
    if (!riwayat.empty()) {
        cout << "\n[RIWAYAT] Aktivitas terakhir: \"" << riwayat.top().keterangan << "\"\n";
    } else {
        cout << "\n[INFO] Riwayat aktivitas kosong.\n";
    }
}

void jumlahAktivitas() {
    cout << "\n[RIWAYAT] Total aktivitas tercatat: " << riwayat.size() << " aktivitas.\n";
}

void tampilkanSemuaAktivitas() {
    if (riwayat.empty()) {
        cout << "\n[INFO] Riwayat aktivitas kosong.\n";
        return;
    }

    stack<Aktivitas> temp = riwayat;
    int urutan = 1;

    cout << "\n======= RIWAYAT SEMUA AKTIVITAS (Terbaru -> Terlama) =======\n";
    while (!temp.empty()) {
        cout << urutan++ << ". " << temp.top().keterangan << "\n";
        temp.pop();
    }
    cout << "============================================================\n";
}

#endif
