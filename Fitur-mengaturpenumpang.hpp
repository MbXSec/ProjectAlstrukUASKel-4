#include <iostream>
#include <string>

using namespace std;

// Struct untuk menyimpan data penumpang
struct Penumpang {
    string nama;
    string nomorTiket;
    string nomorBagasi;
    Penumpang* next; // Pointer ke node berikutnya
};

// Fungsi untuk menambah penumpang di awal list (Insert First)
void tambahPenumpang(Penumpang* &head, string nama, string tiket, string bagasi) {
    Penumpang* baru = new Penumpang();
    baru->nama = nama;
    baru->nomorTiket = tiket;
    baru->nomorBagasi = bagasi;
    baru->next = head;
    head = baru;
    cout << "Penumpang " << nama << " berhasil ditambahkan!\n";
}

// Fungsi untuk mencari penumpang berdasarkan Nomor Bagasi
void cariNomorBagasi(Penumpang* head, string bagasiDicari) {
    Penumpang* temp = head;
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
void tampilkanSemua(Penumpang* head) {
    if (head == nullptr) {
        cout << "Daftar penumpang kosong.\n";
        return;
    }

    Penumpang* temp = head;
    cout << "\n=== DAFTAR PENUMPANG ===\n";
    while (temp != nullptr) {
        cout << "Nama: " << temp->nama 
             << " | Tiket: " << temp->nomorTiket 
             << " | Bagasi: " << temp->nomorBagasi << "\n";
        temp = temp->next;
    }
    cout << "========================\n";
}

int main() {
    Penumpang* daftarPenumpang = nullptr; // Inisialisasi list kosong

    // 1. Menambah data penumpang
    tambahPenumpang(daftarPenumpang, "Andi Wijaya", "TK-001", "BGG-99A");
    tambahPenumpang(daftarPenumpang, "Siti Rahma", "TK-002", "BGG-45B");
    tambahPenumpang(daftarPenumpang, "Budi Santoso", "TK-003", "BGG-12C");

    // 2. Menampilkan semua penumpang
    tampilkanSemua(daftarPenumpang);

    // 3. Melakukan pencarian nomor bagasi
    cariNomorBagasi(daftarPenumpang, "BGG-45B"); // Kasus: Bagasi ada
    cariNomorBagasi(daftarPenumpang, "BGG-777"); // Kasus: Bagasi tidak ada

    return 0;
}
