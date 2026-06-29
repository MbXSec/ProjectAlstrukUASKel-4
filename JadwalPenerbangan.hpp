#ifndef JADWAL_PENERBANGAN_HPP
#define JADWAL_PENERBANGAN_HPP

#include <iostream>
#include <string>
#include "RiwayatAktivitasBandara.hpp"

using namespace std;

struct Penerbangan {
    string nomorPesawat;
    string maskapai;
    string tujuan;
    int jamTerbang;
    
    Penerbangan* next;
    Penerbangan* prev;
};

void tambahJadwal(Penerbangan*& head, Penerbangan*& tail, string no, string maskapai, string tujuan, int jam) {
    Penerbangan* nodeBaru = new Penerbangan();
    nodeBaru->nomorPesawat = no;
    nodeBaru->maskapai = maskapai;
    nodeBaru->tujuan = tujuan;
    nodeBaru->jamTerbang = jam;
    nodeBaru->next = nullptr;
    nodeBaru->prev = nullptr;

    if (head == nullptr) {
        head = tail = nodeBaru;
    } else {
        tail->next = nodeBaru;
        nodeBaru->prev = tail;
        tail = nodeBaru;
    }
    cout << "\n[SUKSES] Jadwal " << no << " berhasil ditambahkan!\n";
    tambahAktivitas("Menambah jadwal penerbangan " + no);
}

void tampilkanJadwalMaju(Penerbangan* head) {
    if (head == nullptr) {
        cout << "\n[INFO] Belum ada jadwal penerbangan.\n";
        return;
    }
    Penerbangan* temp = head;
    cout << "\n=================== DAFTAR JADWAL PENERBANGAN (URUTAN AWAL) ===================\n";
    cout << "No Pesawat\t| Maskapai\t| Tujuan\t| Jam Terbang\n";
    cout << "-------------------------------------------------------------------------------\n";
    while (temp != nullptr) {
        cout << temp->nomorPesawat << "\t\t| " << temp->maskapai << "\t\t| " 
             << temp->tujuan << "\t| " << temp->jamTerbang << "\n";
        temp = temp->next;
    }
}

void ubahJadwal(Penerbangan* head, string no) {
    Penerbangan* temp = head;
    while (temp != nullptr) {
        if (temp->nomorPesawat == no) {
            cout << "\n--- Data Lama Ditemukan. Masukkan Data Baru ---\n";
            cout << "Masukkan Maskapai Baru: "; getline(cin >> ws, temp->maskapai);
            cout << "Masukkan Tujuan Baru  : "; getline(cin >> ws, temp->tujuan);
            cout << "Masukkan Jam Baru(int): "; cin >> temp->jamTerbang;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "[EROR] Jam harus berupa angka!\n";
                return;
            }
            cout << "[SUKSES] Jadwal " << no << " berhasil diperbarui!\n";
            tambahAktivitas("Mengubah jadwal penerbangan " + no);
            return;
        }
        temp = temp->next;
    }
    cout << "\n[EROR] Nomor pesawat " << no << " tidak ditemukan.\n";
}

void hapusJadwal(Penerbangan*& head, Penerbangan*& tail, string no) {
    if (head == nullptr) return;

    Penerbangan* temp = head;
    while (temp != nullptr) {
        if (temp->nomorPesawat == no) {
            if (temp == head) {
                head = head->next;
                if (head != nullptr) head->prev = nullptr;
                else tail = nullptr;
            }
            else if (temp == tail) {
                tail = tail->prev;
                tail->next = nullptr;
            }
            else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            delete temp;
            cout << "\n[SUKSES] Jadwal " << no << " berhasil dihapus!\n";
            tambahAktivitas("Menghapus jadwal penerbangan " + no);
            return;
        }
        temp = temp->next;
    }
    cout << "\n[EROR] Nomor pesawat " << no << " tidak ditemukan.\n";
}

void urutkanJadwal(Penerbangan* head) {
    if (head == nullptr) {
        cout << "\n[INFO] Belum ada jadwal penerbangan.\n";
        return;
    }
    if (head->next == nullptr) {
        cout << "\n[INFO] Hanya ada satu jadwal, tidak perlu diurutkan.\n";
        return;
    }

    bool swapped;
    Penerbangan* ptr1;
    Penerbangan* lptr = nullptr;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->jamTerbang > ptr1->next->jamTerbang) {
                swap(ptr1->nomorPesawat, ptr1->next->nomorPesawat);
                swap(ptr1->maskapai,     ptr1->next->maskapai);
                swap(ptr1->tujuan,       ptr1->next->tujuan);
                swap(ptr1->jamTerbang,   ptr1->next->jamTerbang);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    cout << "\n[SUKSES] Jadwal berhasil diurutkan berdasarkan jam terbang terawal!\n";
    tambahAktivitas("Mengurutkan jadwal penerbangan");
}

#endif
