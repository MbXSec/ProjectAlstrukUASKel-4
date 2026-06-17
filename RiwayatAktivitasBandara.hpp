#include <iostream>
#include <stack>
using namespace std;

struct Aktivitas {
	string keterangan;
};

stack<Aktivitas> riwayat;

//Tambah aktivitas
void tambahAktivitas() {
	Aktivitas a;
	cout << "Masukkan aktivitas: ";
	cin.ignore();
	getline(cin, a.keterangan);
	riwayat.push(a);
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


















