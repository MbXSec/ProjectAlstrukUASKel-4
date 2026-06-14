#include <iostream>
#include <string>
#include "Antrean.hpp"
#include "Lajur.hpp"
#include "Penumpang.hpp"
using namespace std;

// Struct untuk Node Doubly Linked List
struct Penerbangan {
    string nomorPesawat;
    string maskapai;
    string tujuan;
    int jamTerbang; // Format angka, misal 1300 untuk jam 13:00
    
    Penerbangan* next; // Pointer ke node setelahnya
    Penerbangan* prev; // Pointer ke node sebelumnya
};

// Fungsi Tambah Jadwal (Insert Last)
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
        tail = nodeBaru; // Pindahkan tail ke node baru
    }
    cout << "\n[SUKSES] Jadwal " << no << " berhasil ditambahkan!\n";
}

// Fungsi Lihat Jadwal (Traversal Maju)
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

// Fungsi Ubah Jadwal berdasarkan Nomor Pesawat
void ubahJadwal(Penerbangan* head, string no) {
    Penerbangan* temp = head;
    while (temp != nullptr) {
        if (temp->nomorPesawat == no) {
            cout << "\n--- Data Lama Ditemukan. Masukkan Data Baru ---\n";
            cout << "Masukkan Maskapai Baru: "; cin >> temp->maskapai;
            cout << "Masukkan Tujuan Baru  : "; cin >> temp->tujuan;
            cout << "Masukkan Jam Baru(int): "; cin >> temp->jamTerbang;
            cout << "[SUKSES] Jadwal " << no << " berhasil diperbarui!\n";
            return;
        }
        temp = temp->next;
    }
    cout << "\n[EROR] Nomor pesawat " << no << " tidak ditemukan.\n";
}

// Fungsi Hapus Jadwal (Delete Node tertentu)
void hapusJadwal(Penerbangan*& head, Penerbangan*& tail, string no) {
    if (head == nullptr) return;

    Penerbangan* temp = head;
    while (temp != nullptr) {
        if (temp->nomorPesawat == no) {
            // Jika node yang dihapus adalah head
            if (temp == head) {
                head = head->next;
                if (head != nullptr) head->prev = nullptr;
                else tail = nullptr; // Jika list jadi kosong
            }
            // Jika node yang dihapus adalah tail
            else if (temp == tail) {
                tail = tail->prev;
                tail->next = nullptr;
            }
            // Jika node di tengah-tengah
            else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            delete temp;
            cout << "\n[SUKSES] Jadwal " << no << " berhasil dihapus!\n";
            return;
        }
        temp = temp->next;
    }
    cout << "\n[EROR] Nomor pesawat " << no << " tidak ditemukan.\n";
}

// Fungsi Sorting Menggunakan Bubble Sort (Berdasarkan Jam Terbang Terawal)
void urutkanJadwal(Penerbangan* head) {
    if (head == nullptr) return;
    
    bool swapped;
    Penerbangan* ptr1;
    Penerbangan* lptr = nullptr;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->jamTerbang > ptr1->next->jamTerbang) {
                // Tukar datanya saja (cara paling aman dan simpel untuk tugas kuliah)
                swap(ptr1->nomorPesawat, ptr1->next->nomorPesawat);
                swap(ptr1->maskapai, ptr1->next->maskapai);
                swap(ptr1->tujuan, ptr1->next->tujuan);
                swap(ptr1->jamTerbang, ptr1->next->jamTerbang);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
    cout << "\n[SUKSES] Jadwal berhasil diurutkan berdasarkan jam terbang terawal!\n";
}

// Menu Utama Aplikasi
int main() {
    Penerbangan* headNode = nullptr;
    Penerbangan* tailNode = nullptr;
    int pilihan;
    string no, maskapai, tujuan;
    int jam;

    do {
        cout << "\n=========================================\n";
        cout << "    SISTEM MANAJEMEN BANDARA (CORE)     \n";
        cout << "=========================================\n";
        cout << "1. Tambah Jadwal Penerbangan\n";
        cout << "2. Tampilkan Semua Jadwal\n";
        cout << "3. Ubah Jadwal Penerbangan\n";
        cout << "4. Hapus Jadwal Penerbangan\n";
        cout << "5. Urutkan Jadwal (Berdasarkan Jam)\n";
        cout << "6. Keluar\n";
        cout << "Pilih Menu [1-6]: "; cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan Nomor Pesawat : "; cin >> no;
                cout << "Masukkan Maskapai      : "; cin >> maskapai;
                cout << "Masukkan Tujuan        : "; cin >> tujuan;
                cout << "Masukkan Jam (ex: 0830): "; cin >> jam;
                tambahJadwal(headNode, tailNode, no, maskapai, tujuan, jam);
                break;
            case 2:
                tampilkanJadwalMaju(headNode);
                break;
            case 3:
                cout << "Masukkan Nomor Pesawat yang mau diubah: "; cin >> no;
                ubahJadwal(headNode, no);
                break;
            case 4:
                cout << "Masukkan Nomor Pesawat yang mau dihapus: "; cin >> no;
                hapusJadwal(headNode, tailNode, no);
                break;
            case 5:
                urutkanJadwal(headNode);
                tampilkanJadwalMaju(headNode);
                break;
            case 6:
                cout << "\nTerima kasih! Program selesai.\n";
                break;
            default:
                cout << "\nPilihan tidak valid!\n";
        }
    } while (pilihan != 6);

    return 0;
}