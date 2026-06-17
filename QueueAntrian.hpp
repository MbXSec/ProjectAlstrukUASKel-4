#ifndef QUEUE_ANTRIAN_HPP
#define QUEUE_ANTRIAN_HPP

#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;

struct Penumpang{
    string nama;
    string kelas;
};

// Queue Antrian Penumpang (Circular Queue)
Penumpang antrian[MAX];
int front = -1;
int rear = -1;

void enqueue(string nama, string kelas){
    if((rear + 1) % MAX == front){
        cout << "Antrian penuh\n";
        return;
    }

    if(front == -1){
        front = 0;
        rear = 0;
    } else {
        rear = (rear + 1) % MAX;
    }

    antrian[rear].nama = nama;
    antrian[rear].kelas = kelas;
    cout << "Penumpang " << nama << " masuk antrian reguler.\n";
}

void dequeue(){
    if(front == -1){
        cout << "Antrian kosong\n";
        return;
    }

    cout << antrian[front].nama << " diproses\n";

    if(front == rear){
        front = -1;
        rear = -1;
    }
    else{
        front = (front + 1) % MAX;
    }
}

void tampilAntrian(){
    if(front == -1){
        cout << "Antrian kosong\n";
        return;
    }

    int i = front;
    while(true){
        cout << antrian[i].nama << " - " << antrian[i].kelas << endl;
        if(i == rear) break;
        i = (i + 1) % MAX;
    }
}

// Priority Queue Business Class (Shift Array)
Penumpang prioritas[MAX];
int jumlah = 0;

void enqueuePrioritas(string nama, string kelas){
    if(jumlah == MAX){
        cout << "Antrian penuh\n";
        return;
    }

    int i = jumlah - 1;

    // Prioritas utama untuk kelas Business
    if(kelas == "Business"){
        while(i >= 0 && prioritas[i].kelas != "Business"){
            prioritas[i + 1] = prioritas[i];
            i--;
        }
    }

    prioritas[i + 1].nama = nama;
    prioritas[i + 1].kelas = kelas;

    jumlah++;
    cout << "Penumpang " << nama << " masuk antrian prioritas.\n";
}

void dequeuePrioritas(){
    if(jumlah == 0){
        cout << "Antrian kosong\n";
        return;
    }

    cout << prioritas[0].nama << " diproses\n";

    for(int i = 0; i < jumlah - 1; i++){
        prioritas[i] = prioritas[i + 1];
    }

    jumlah--;
}

void tampilPrioritas(){
    if(jumlah == 0){
        cout << "Antrian kosong\n";
        return;
    }

    for(int i = 0; i < jumlah; i++){
        cout << prioritas[i].nama << " - " << prioritas[i].kelas << endl;
    }
}

#endif
