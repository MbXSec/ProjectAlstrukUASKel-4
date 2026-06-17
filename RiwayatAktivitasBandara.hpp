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

//Tambah aktivitas
void tambahAktivitas(string keterangan) {
	Aktivitas a;
	a.keterangan = keterangan;
	riwayat.push(a);
    cout << "[RIWAYAT] Aktivitas tercatat: " << keterangan << endl;
}

//Hapus aktivitas terakhir
void hapusAktivitas() {
	if (!riwayat.empty()) {
		cout << "Aktivitas dihapus: " << riwayat.top().keterangan << endl;
		riwayat.pop();
	} else {
		cout << "Riwayat kosong!\n";
	}
}

//Lihat aktivitas terakhir
void lihatAktivitas() {
	if (!riwayat.empty()) {
		cout << "Aktivitas terakhir: " << riwayat.top().keterangan << endl;
	} else {
		cout << "Riwayat kosong!\n";
	}
}

//Tampilkan jumlah aktivitas
void jumlahAktivitas() {
	cout << "Jumlah aktivitas: " << riwayat.size() << endl;
}

#endif
