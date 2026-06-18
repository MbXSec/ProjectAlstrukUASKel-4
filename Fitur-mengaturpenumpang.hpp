#ifndef FITUR_MENGATUR_PENUMPANG_HPP
#define FITUR_MENGATUR_PENUMPANG_HPP

#include <iostream>
#include <string>

using namespace std;

// Struct untuk menyimpan data penumpang
struct PenumpangBagasi {
    string nama;
    string nomorTiket;
    string nomorBagasi;
    PenumpangBagasi* next; // Pointer ke node berikutnya
};

// Fungsi untuk menambah penumpang di awal list (Insert First)
void tambahPenumpangBagasi(PenumpangBagasi* &head, string nama, string tiket, string bagasi) {
    PenumpangBagasi* baru = new PenumpangBagasi();
    baru->nama = nama;
    baru->nomorTiket = tiket;
    baru->nomorBagasi = bagasi;
    baru->next = head;
    head = baru;
    cout << "Penumpang " << nama << " berhasil ditambahkan!\n";
}

// Fungsi untuk mencari penumpang berdasarkan Nomor Bagasi
void cariNomorBagasi(PenumpangBagasi* head, string bagasiDicari) {
    PenumpangBagasi* temp = head;
    bool ditemukan = false;

    cout << "\n--- Hasil Pencarian Bagasi: " << bagasiDicari << " ---\n";
    
    while (temp != nullptr) {
        if (temp->nomorBagasi == bagasiDicari) {
            cout << "Status      : DITEMUKAN\n";
            cout << "Nama        : " << temp->nama << "\n";
            cout << "Nomor Tiket : " << temp->nomorTiket << "\n";
            cout << "Nomor Bagasi: " << temp->nomorBagasi << "\n";
            ditemukan = true;
            break; // Hentikan pencarian jika sudah ketemu (asumsi nomor bagasi unik)
        }
        temp = temp->next;
    }

    if (!ditemukan) {
        cout << "Maaf, penumpang dengan nomor bagasi " << bagasiDicari << " tidak ditemukan.\n";
    }
    cout << "---------------------------------------\n";
}

// Fungsi untuk menampilkan semua data penumpang
void tampilkanSemuaBagasi(PenumpangBagasi* head) {
    if (head == nullptr) {
        cout << "Daftar penumpang kosong.\n";
        return;
    }

    PenumpangBagasi* temp = head;
    cout << "\n=== DAFTAR PENUMPANG ===\n";
    while (temp != nullptr) {
        cout << "Nama: " << temp->nama 
             << " | Tiket: " << temp->nomorTiket 
             << " | Bagasi: " << temp->nomorBagasi << "\n";
        temp = temp->next;
    }
    cout << "========================\n";
}

#endif
