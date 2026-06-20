#ifndef QUEUE_ANTRIAN_HPP
#define QUEUE_ANTRIAN_HPP

#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;

struct Penumpang {
    string nama;
    string kelas;
};

Penumpang antrian[MAX];
int front = -1;
int rear  = -1;

bool antrianPenuh() {
    return (front != -1) && ((rear + 1) % MAX == front);
}

bool antrianKosong() {
    return front == -1;
}

void enqueue(string nama, string kelas) {
    if (antrianPenuh()) {
        cout << "\n[INFO] Antrian reguler penuh (maks " << MAX << " orang).\n";
        return;
    }

    if (antrianKosong()) {
        front = 0;
        rear  = 0;
    } else {
        rear = (rear + 1) % MAX;
    }

    antrian[rear].nama  = nama;
    antrian[rear].kelas = kelas;
    cout << "Penumpang " << nama << " masuk antrian reguler.\n";
}

void dequeue() {
    if (antrianKosong()) {
        cout << "\n[INFO] Antrian reguler kosong, tidak ada yang diproses.\n";
        return;
    }

    cout << "[PROSES] " << antrian[front].nama << " sedang diproses.\n";

    if (front == rear) {
        front = -1;
        rear  = -1;
    } else {
        front = (front + 1) % MAX;
    }
}

void tampilAntrian() {
    if (antrianKosong()) {
        cout << "\n[INFO] Antrian reguler kosong.\n";
        return;
    }

    cout << "\n=== ANTRIAN REGULER ===\n";
    int i = front;
    int urutan = 1;
    while (true) {
        cout << urutan++ << ". " << antrian[i].nama
             << " - " << antrian[i].kelas << "\n";
        if (i == rear) break;
        i = (i + 1) % MAX;
    }
    cout << "======================\n";
}

Penumpang prioritas[MAX];
int jumlah = 0;

void enqueuePrioritas(string nama, string kelas) {
    if (jumlah == MAX) {
        cout << "\n[INFO] Antrian prioritas penuh (maks " << MAX << " orang).\n";
        return;
    }

    int posInsert = jumlah;

    if (kelas == "Business") {
        posInsert = 0;
        while (posInsert < jumlah && prioritas[posInsert].kelas == "Business") {
            posInsert++;
        }
    }

    for (int i = jumlah; i > posInsert; i--) {
        prioritas[i] = prioritas[i - 1];
    }

    prioritas[posInsert].nama  = nama;
    prioritas[posInsert].kelas = kelas;
    jumlah++;

    cout << "Penumpang " << nama << " (" << kelas
         << ") masuk antrian prioritas di posisi " << posInsert + 1 << ".\n";
}

void dequeuePrioritas() {
    if (jumlah == 0) {
        cout << "\n[INFO] Antrian prioritas kosong, tidak ada yang diproses.\n";
        return;
    }

    cout << "[PROSES] " << prioritas[0].nama
         << " (" << prioritas[0].kelas << ") sedang diproses.\n";

    for (int i = 0; i < jumlah - 1; i++) {
        prioritas[i] = prioritas[i + 1];
    }
    jumlah--;
}

void tampilPrioritas() {
    if (jumlah == 0) {
        cout << "\n[INFO] Antrian prioritas kosong.\n";
        return;
    }

    cout << "\n=== ANTRIAN PRIORITAS ===\n";
    for (int i = 0; i < jumlah; i++) {
        cout << i + 1 << ". " << prioritas[i].nama
             << " - " << prioritas[i].kelas << "\n";
    }
    cout << "=========================\n";
}

#endif
