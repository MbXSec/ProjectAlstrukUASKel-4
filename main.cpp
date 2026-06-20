#include <iostream>
#include <string>
#include "QueueAntrian.hpp"
#include "RiwayatAktivitasBandara.hpp"
#include "Fitur-mengaturpenumpang.hpp"
#include "lajur pesawat.hpp"

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

int main() {
    Penerbangan* headNode = nullptr;
    Penerbangan* tailNode = nullptr;
    int pilihan;
    string no, maskapai, tujuan;
    int jam;
    string namaPenumpang, kelasPenumpang, aktivitasBaru;
    PenumpangBagasi* daftarPenumpangBagasi = nullptr;
    string tiket, bagasi;
    int nomorLajur, kapasitasLajur;

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
        cout << "16. Tampilkan Semua Riwayat Aktivitas\n";
        cout << "--- BAGASI PENUMPANG ---\n";
        cout << "17. Tambah Data Penumpang (Bagasi)\n";
        cout << "18. Tampilkan Semua Penumpang (Bagasi)\n";
        cout << "19. Cari Penumpang Berdasarkan Bagasi\n";
        cout << "--- LAJUR KEBERANGKATAN (Linked List) ---\n";
        cout << "20. Tambah Lajur Keberangkatan\n";
        cout << "21. Tampilkan Semua Lajur\n";
        cout << "22. Ubah Status Lajur (Aktif/Tutup)\n";
        cout << "23. Hapus Lajur Keberangkatan\n";
        cout << "0. Keluar\n";
        cout << "Pilih Menu [0-23]: "; cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n[EROR] Input tidak valid! Masukkan angka.\n";
            continue;
        }

        switch (pilihan) {
            case 1:
                cout << "Masukkan Nomor Pesawat : "; getline(cin >> ws, no);
                cout << "Masukkan Maskapai      : "; getline(cin >> ws, maskapai);
                cout << "Masukkan Tujuan        : "; getline(cin >> ws, tujuan);
                cout << "Masukkan Jam (ex: 0830): "; cin >> jam;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "[EROR] Jam harus berupa angka!\n";
                    continue;
                }
                tambahJadwal(headNode, tailNode, no, maskapai, tujuan, jam);
                break;
            case 2:
                tampilkanJadwalMaju(headNode);
                break;
            case 3:
                cout << "Masukkan Nomor Pesawat yang mau diubah: "; getline(cin >> ws, no);
                ubahJadwal(headNode, no);
                break;
            case 4:
                cout << "Masukkan Nomor Pesawat yang mau dihapus: "; getline(cin >> ws, no);
                hapusJadwal(headNode, tailNode, no);
                break;
            case 5:
                urutkanJadwal(headNode);
                tampilkanJadwalMaju(headNode);
                break;
            case 6:
                cout << "Masukkan Nama Penumpang: "; getline(cin >> ws, namaPenumpang);
                cout << "Masukkan Kelas Penumpang (Economy/dll): "; getline(cin >> ws, kelasPenumpang);
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
                cout << "Masukkan Nama Penumpang: "; getline(cin >> ws, namaPenumpang);
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
                getline(cin >> ws, aktivitasBaru);
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
                tampilkanSemuaAktivitas();
                break;
            case 17:
                cout << "Masukkan Nama Penumpang: ";
                getline(cin >> ws, namaPenumpang);
                cout << "Masukkan Nomor Tiket: "; getline(cin >> ws, tiket);
                cout << "Masukkan Nomor Bagasi: "; getline(cin >> ws, bagasi);
                tambahPenumpangBagasi(daftarPenumpangBagasi, namaPenumpang, tiket, bagasi);
                tambahAktivitas("Menambah data penumpang dan bagasi " + namaPenumpang);
                break;
            case 18:
                tampilkanSemuaBagasi(daftarPenumpangBagasi);
                break;
            case 19:
                cout << "Masukkan Nomor Bagasi yang dicari: "; getline(cin >> ws, bagasi);
                cariNomorBagasi(daftarPenumpangBagasi, bagasi);
                break;
            case 20:
                cout << "Masukkan Nomor Lajur   : "; cin >> nomorLajur;
                if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); cout << "[EROR] Nomor harus angka!\n"; continue; }
                cout << "Masukkan Nama Maskapai : "; getline(cin >> ws, maskapai);
                cout << "Masukkan Kapasitas     : "; cin >> kapasitasLajur;
                if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); cout << "[EROR] Kapasitas harus angka!\n"; continue; }
                tambahLajur(nomorLajur, maskapai, kapasitasLajur);
                tambahAktivitas("Menambah lajur keberangkatan nomor " + to_string(nomorLajur));
                break;
            case 21:
                tampilkanLajur();
                break;
            case 22:
                cout << "Masukkan Nomor Lajur yang statusnya diubah: "; cin >> nomorLajur;
                if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); cout << "[EROR] Nomor harus angka!\n"; continue; }
                ubahStatusLajur(nomorLajur);
                tambahAktivitas("Mengubah status lajur nomor " + to_string(nomorLajur));
                break;
            case 23:
                cout << "Masukkan Nomor Lajur yang dihapus: "; cin >> nomorLajur;
                if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); cout << "[EROR] Nomor harus angka!\n"; continue; }
                hapusLajur(nomorLajur);
                tambahAktivitas("Menghapus lajur keberangkatan nomor " + to_string(nomorLajur));
                break;
            case 0:
                cout << "\nTerima kasih! Program selesai.\n";
                break;
            default:
                cout << "\n[INFO] Pilihan tidak valid! Masukkan angka 0-23.\n";
        }
    } while (pilihan != 0);

    return 0;
}
