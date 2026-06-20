#ifndef FITUR_KAMU_HPP
#define FITUR_KAMU_HPP

#include <iostream>
#include <string>
#include <vector>

// Menggunakan namespace kelompok (opsional, sesuaikan dengan setup proyek)
namespace ProyekAlstruk {

    // Contoh Struktur Data untuk Node atau Elemen (misal: Linked List / Tree / Graph)
    struct Node {
        int data;
        Node* next;
        
        // Constructor data
        Node(int val) : data(val), next(NULL) {}
    };

    // Contoh Class atau Kumpulan Fungsi untuk Fitur Tugasmu
    class ManajerFitur {
    private:
        Node* head;

    public:
        // Constructor
        ManajerFitur() : head(NULL) {}

        // Fungsi Tambah Data (Contoh Implementasi Alstruk)
        void tambahData(int nilai) {
            Node* nodeBaru = new Node(nilai);
            if (!head) {
                head = nodeBaru;
                return;
            }
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = nodeBaru;
        }

        // Fungsi Tampilkan Data
        void cetakData() const {
            Node* temp = head;
            if (!temp) {
                std::cout << "Data kosong!\n";
                return;
            }
            while (temp) {
                std::cout << temp->data << " -> ";
                temp = temp->next;
            }
            std::cout << "NULL\n";
        }

        // Destructor untuk mencegah kebocoran memori (Memory Leak)
        ~ManajerFitur() {
            Node* temp = head;
            while (temp) {
                Node* nextNode = temp->next;
                delete temp;
                temp = nextNode;
            }
        }
    };

} // namespace ProyekAlstruk

#endif // FITUR_KAMU_HPP
