#ifndef LAJUR_PESAWAT_HPP
#define LAJUR_PESAWAT_HPP

#include <iostream>
#include <string>
using namespace std;

struct LajurKeberangkatan {
    int    nomorLajur;
    string namaMaskapai;
    string statusLajur;
    int    kapasitas;
    LajurKeberangkatan* next;
};

LajurKeberangkatan* headLajur = nullptr;

void tambahLajur(int nomorLajur, string namaMaskapai, int kapasitas) {
    LajurKeberangkatan* cek = headLajur;
    while (cek != nullptr) {
        if (cek->nomorLajur == nomorLajur) {
            cout << "\n[EROR] Lajur nomor " << nomorLajur << " sudah ada!\n";
            return;
        }
        cek = cek->next;
    }

    if (kapasitas <= 0) {
        cout << "\n[EROR] Kapasitas harus lebih dari 0!\n";
        return;
    }

    LajurKeberangkatan* baru = new LajurKeberangkatan();
    baru->nomorLajur   = nomorLajur;
    baru->namaMaskapai = namaMaskapai;
    baru->statusLajur  = "Aktif";
    baru->kapasitas    = kapasitas;
    baru->next         = nullptr;

    if (headLajur == nullptr) {
        headLajur = baru;
    } else {
        LajurKeberangkatan* temp = headLajur;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = baru;
    }

    cout << "\n[SUKSES] Lajur " << nomorLajur
         << " (" << namaMaskapai << ") berhasil ditambahkan!\n";
}

void tampilkanLajur() {
    if (headLajur == nullptr) {
        cout << "\n[INFO] Belum ada lajur keberangkatan.\n";
        return;
    }

    cout << "\n============== DAFTAR LAJUR KEBERANGKATAN ==============\n";
    cout << "No Lajur | Maskapai             | Kapasitas | Status\n";
    cout << "--------------------------------------------------------\n";

    LajurKeberangkatan* temp = headLajur;
    while (temp != nullptr) {
        string noStr = to_string(temp->nomorLajur);
        cout << noStr;
        for (int i = noStr.size(); i < 9; i++) cout << ' ';
        cout << "| ";

        cout << temp->namaMaskapai;
        for (int i = temp->namaMaskapai.size(); i < 21; i++) cout << ' ';
        cout << "| ";

        string kapStr = to_string(temp->kapasitas);
        cout << kapStr;
        for (int i = kapStr.size(); i < 10; i++) cout << ' ';
        cout << "| ";

        cout << temp->statusLajur << "\n";
        temp = temp->next;
    }
    cout << "========================================================\n";
}

void ubahStatusLajur(int nomorLajur) {
    LajurKeberangkatan* temp = headLajur;
    while (temp != nullptr) {
        if (temp->nomorLajur == nomorLajur) {
            if (temp->statusLajur == "Aktif") {
                temp->statusLajur = "Tutup";
                cout << "\n[SUKSES] Lajur " << nomorLajur << " sekarang DITUTUP.\n";
            } else {
                temp->statusLajur = "Aktif";
                cout << "\n[SUKSES] Lajur " << nomorLajur << " sekarang AKTIF kembali.\n";
            }
            return;
        }
        temp = temp->next;
    }
    cout << "\n[EROR] Lajur nomor " << nomorLajur << " tidak ditemukan.\n";
}

void hapusLajur(int nomorLajur) {
    if (headLajur == nullptr) {
        cout << "\n[INFO] Belum ada lajur keberangkatan.\n";
        return;
    }

    if (headLajur->nomorLajur == nomorLajur) {
        LajurKeberangkatan* hapus = headLajur;
        headLajur = headLajur->next;
        delete hapus;
        cout << "\n[SUKSES] Lajur " << nomorLajur << " berhasil dihapus!\n";
        return;
    }

    LajurKeberangkatan* prev = headLajur;
    LajurKeberangkatan* curr = headLajur->next;
    while (curr != nullptr) {
        if (curr->nomorLajur == nomorLajur) {
            prev->next = curr->next;
            delete curr;
            cout << "\n[SUKSES] Lajur " << nomorLajur << " berhasil dihapus!\n";
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "\n[EROR] Lajur nomor " << nomorLajur << " tidak ditemukan.\n";
}

#endif
