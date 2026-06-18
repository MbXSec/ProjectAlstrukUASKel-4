#include <iostream>
#include <string>
#include "QueueAntrian.hpp"
#include "RiwayatAktivitasBandara.hpp"
#include "Fitur-mengaturpenumpang.hpp"

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
    tambahAktivitas("Menambah jadwal penerbangan " + no);
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
            tambahAktivitas("Mengubah jadwal penerbangan " + no);
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
            tambahAktivitas("Menghapus jadwal penerbangan " + no);
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
    tambahAktivitas("Mengurutkan jadwal penerbangan");
}

// Menu Utama Aplikasi
int main() {
    Penerbangan* headNode = nullptr;
    Penerbangan* tailNode = nullptr;
    int pilihan;
    string no, maskapai, tujuan;
    int jam;
    string namaPenumpang, kelasPenumpang, aktivitasBaru;
    PenumpangBagasi* daftarPenumpangBagasi = nullptr;
    string tiket, bagasi;

    do {
        cout << "\n======================================================\n";
        cout << "               SISTEM MANAJEMEN BANDARA               \n";
        cout << "======================================================\n";
        cout << "--- JADWAL PENERBANGAN (Linked List) ---\n";
        cout << "1. Tambah Jadwal Penerbangan\n";
        cout << "2. Tampilkan Semua Jadwal\n";
        cout << "3. Ubah Jadwal Penerbangan\n";
        cout << "4. Hapus Jadwal Penerbangan\n";
        cout << "5. Urutkan Jadwal (Berdasarkan Jam)\n";
        cout << "--- ANTRIAN PENUMPANG (Queue) ---\n";
        cout << "6. Tambah Antrian Reguler\n";
        cout << "7. Proses Antrian Reguler\n";
        cout << "8. Tampilkan Antrian Reguler\n";
        cout << "9. Tambah Antrian Prioritas (Business)\n";
        cout << "10. Proses Antrian Prioritas\n";
        cout << "11. Tampilkan Antrian Prioritas\n";
        cout << "--- RIWAYAT AKTIVITAS (Stack) ---\n";
        cout << "12. Tambah Catatan Aktivitas Manual\n";
        cout << "13. Hapus Riwayat Terakhir (Undo)\n";
        cout << "14. Lihat Riwayat Terakhir\n";
        cout << "15. Tampilkan Jumlah Riwayat\n";
        cout << "--- BAGASI PENUMPANG ---\n";
        cout << "16. Tambah Data Penumpang (Bagasi)\n";
        cout << "17. Tampilkan Semua Penumpang (Bagasi)\n";
        cout << "18. Cari Penumpang Berdasarkan Bagasi\n";
        cout << "0. Keluar\n";
        cout << "Pilih Menu [0-18]: "; cin >> pilihan;

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
                cout << "Masukkan Nama Penumpang: "; cin >> namaPenumpang;
                cout << "Masukkan Kelas Penumpang (Economy/dll): "; cin >> kelasPenumpang;
                enqueue(namaPenumpang, kelasPenumpang);
                tambahAktivitas("Menambah antrian reguler penumpang " + namaPenumpang);
                break;
            case 7:
                dequeue();
                tambahAktivitas("Memproses antrian reguler");
                break;
            case 8:
                tampilAntrian();
                break;
            case 9:
                cout << "Masukkan Nama Penumpang: "; cin >> namaPenumpang;
                kelasPenumpang = "Business";
                enqueuePrioritas(namaPenumpang, kelasPenumpang);
                tambahAktivitas("Menambah antrian prioritas penumpang " + namaPenumpang);
                break;
            case 10:
                dequeuePrioritas();
                tambahAktivitas("Memproses antrian prioritas");
                break;
            case 11:
                tampilPrioritas();
                break;
            case 12:
                cout << "Masukkan aktivitas: ";
                cin.ignore();
                getline(cin, aktivitasBaru);
                tambahAktivitas(aktivitasBaru);
                break;
            case 13:
                hapusAktivitas();
                break;
            case 14:
                lihatAktivitas();
                break;
            case 15:
                jumlahAktivitas();
                break;
            case 16:
                cout << "Masukkan Nama Penumpang: ";
                cin.ignore();
                getline(cin, namaPenumpang);
                cout << "Masukkan Nomor Tiket: "; cin >> tiket;
                cout << "Masukkan Nomor Bagasi: "; cin >> bagasi;
                tambahPenumpangBagasi(daftarPenumpangBagasi, namaPenumpang, tiket, bagasi);
                tambahAktivitas("Menambah data penumpang dan bagasi " + namaPenumpang);
                break;
            case 17:
                tampilkanSemuaBagasi(daftarPenumpangBagasi);
                break;
            case 18:
                cout << "Masukkan Nomor Bagasi yang dicari: "; cin >> bagasi;
                cariNomorBagasi(daftarPenumpangBagasi, bagasi);
                break;
            case 0:
                cout << "\nTerima kasih! Program selesai.\n";
                break;
            default:
                cout << "\nPilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    return 0;
}
