#include <iostream>
#include <string>
#include "QueueAntrian.hpp"
#include "RiwayatAktivitasBandara.hpp"
#include "Fitur-mengaturpenumpang.hpp"
#include "lajur pesawat.hpp"

using namespace std;

int main() {
    int pilihan;
    string maskapai;
    string namaPenumpang, kelasPenumpang, aktivitasBaru;
    PenumpangBagasi* daftarPenumpangBagasi = nullptr;
    string tiket, bagasi;
    int nomorLajur, kapasitasLajur;

    do {
        cout << "\n======================================================\n";
        cout << "               SISTEM MANAJEMEN BANDARA               \n";
        cout << "======================================================\n";
        cout << "--- ANTRIAN PENUMPANG ---\n";
        cout << "1. Tambah Antrian Reguler\n";
        cout << "2. Proses Antrian Reguler\n";
        cout << "3. Tampilkan Antrian Reguler\n";
        cout << "4. Tambah Antrian Prioritas (Business)\n";
        cout << "5. Proses Antrian Prioritas\n";
        cout << "6. Tampilkan Antrian Prioritas\n\n";
        cout << "--- RIWAYAT AKTIVITAS ---\n";
        cout << "7. Tambah Catatan Aktivitas Manual\n";
        cout << "8. Hapus Riwayat Terakhir (Undo)\n";
        cout << "9. Lihat Riwayat Terakhir\n";
        cout << "10. Tampilkan Jumlah Riwayat\n";
        cout << "11. Tampilkan Semua Riwayat Aktivitas\n\n";
        cout << "--- BAGASI PENUMPANG ---\n";
        cout << "12. Tambah Data Penumpang (Bagasi)\n";
        cout << "13. Tampilkan Semua Penumpang (Bagasi)\n";
        cout << "14. Cari Penumpang Berdasarkan Bagasi\n\n";
        cout << "--- LAJUR KEBERANGKATAN ---\n";
        cout << "15. Tambah Lajur Keberangkatan\n";
        cout << "16. Tampilkan Semua Lajur\n";
        cout << "17. Ubah Status Lajur (Aktif/Tutup)\n";
        cout << "18. Hapus Lajur Keberangkatan\n";
        cout << "0. Keluar\n";
        cout << "Pilih Menu [0-18]: "; cin >> pilihan;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n[EROR] Input tidak valid! Masukkan angka.\n";
            continue;
        }

        switch (pilihan) {
            case 1:
                cout << "Masukkan Nama Penumpang: "; getline(cin >> ws, namaPenumpang);
                cout << "Masukkan Kelas Penumpang (Economy/dll): "; getline(cin >> ws, kelasPenumpang);
                enqueue(namaPenumpang, kelasPenumpang);
                tambahAktivitas("Menambah antrian reguler penumpang " + namaPenumpang);
                break;
            case 2:
                dequeue();
                tambahAktivitas("Memproses antrian reguler");
                break;
            case 3:
                tampilAntrian();
                break;
            case 4:
                cout << "Masukkan Nama Penumpang: "; getline(cin >> ws, namaPenumpang);
                kelasPenumpang = "Business";
                enqueuePrioritas(namaPenumpang, kelasPenumpang);
                tambahAktivitas("Menambah antrian prioritas penumpang " + namaPenumpang);
                break;
            case 5:
                dequeuePrioritas();
                tambahAktivitas("Memproses antrian prioritas");
                break;
            case 6:
                tampilPrioritas();
                break;
            case 7:
                cout << "Masukkan aktivitas: ";
                getline(cin >> ws, aktivitasBaru);
                tambahAktivitas(aktivitasBaru);
                break;
            case 8:
                hapusAktivitas();
                break;
            case 9:
                lihatAktivitas();
                break;
            case 10:
                jumlahAktivitas();
                break;
            case 11:
                tampilkanSemuaAktivitas();
                break;
            case 12:
                cout << "Masukkan Nama Penumpang: ";
                getline(cin >> ws, namaPenumpang);
                cout << "Masukkan Nomor Tiket: "; getline(cin >> ws, tiket);
                cout << "Masukkan Nomor Bagasi: "; getline(cin >> ws, bagasi);
                tambahPenumpangBagasi(daftarPenumpangBagasi, namaPenumpang, tiket, bagasi);
                tambahAktivitas("Menambah data penumpang dan bagasi " + namaPenumpang);
                break;
            case 13:
                tampilkanSemuaBagasi(daftarPenumpangBagasi);
                break;
            case 14:
                cout << "Masukkan Nomor Bagasi yang dicari: "; getline(cin >> ws, bagasi);
                cariNomorBagasi(daftarPenumpangBagasi, bagasi);
                break;
            case 15:
                cout << "Masukkan Nomor Lajur   : "; cin >> nomorLajur;
                if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); cout << "[EROR] Nomor harus angka!\n"; continue; }
                cout << "Masukkan Nama Maskapai : "; getline(cin >> ws, maskapai);
                cout << "Masukkan Kapasitas     : "; cin >> kapasitasLajur;
                if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); cout << "[EROR] Kapasitas harus angka!\n"; continue; }
                tambahLajur(nomorLajur, maskapai, kapasitasLajur);
                tambahAktivitas("Menambah lajur keberangkatan nomor " + to_string(nomorLajur));
                break;
            case 16:
                tampilkanLajur();
                break;
            case 17:
                cout << "Masukkan Nomor Lajur yang statusnya diubah: "; cin >> nomorLajur;
                if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); cout << "[EROR] Nomor harus angka!\n"; continue; }
                ubahStatusLajur(nomorLajur);
                tambahAktivitas("Mengubah status lajur nomor " + to_string(nomorLajur));
                break;
            case 18:
                cout << "Masukkan Nomor Lajur yang dihapus: "; cin >> nomorLajur;
                if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); cout << "[EROR] Nomor harus angka!\n"; continue; }
                hapusLajur(nomorLajur);
                tambahAktivitas("Menghapus lajur keberangkatan nomor " + to_string(nomorLajur));
                break;
            case 0:
                cout << "\nTerima kasih! Program selesai.\n";
                break;
            default:
                cout << "\n[INFO] Pilihan tidak valid! Masukkan angka 0-18.\n";
        }
    } while (pilihan != 0);

    return 0;
}
