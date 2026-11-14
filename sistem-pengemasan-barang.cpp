#include <iostream>
using namespace std;

const int MAX_ANTRIAN = 5;

struct Barang {
    int id;
    char nama[50];
};

// DOUBLY LINKED LIST
struct DNode {
    Barang data;
    DNode* next, *prev;
};

class DList {
    DNode* head, *tail;
    int size;

public:
    DList() : head(NULL), tail(NULL), size(0) {}
    ~DList() {
        while (head) {
            DNode *t = head;
            head = head->next;
            delete t;
        }
    }

    bool kosong() { 
        return head == NULL; 
    }
    int jumlah() { 
        return size; 
    }

    void pushFront(const Barang &b) {
        DNode* n = new DNode{b, NULL, head};
        if (head) {
            head->prev = n;
        } else {
            tail = n;
        }
        head = n;
        size++;
    }

    void pushBack(const Barang &b) {
        DNode* n = new DNode{b, tail, NULL};
        if (tail) {
            tail->next = n;
        } else {
            head = n;
        }
        tail = n;
        size++;
    }

    bool popFront(Barang &out) {
        if (!head) {
            return false;
        }
        DNode *t = head;
        out = head->data;
        head = head->next;
        if (head) {
            head->prev = NULL;
        } else {
            tail = NULL;
        }
        delete t;
        size--;
        return true;
    }

    bool popBack(Barang &out) {
        if (!tail) {
            return false;
        }
        DNode *t = tail;
        out = tail->data;
        tail = tail->prev;
        if (tail) {
            tail->next = NULL;
        } else {
            head = NULL;
        }
        delete t;
        size--;
        return true;
    }

    void cetakMaju() {
        int i = size;
        for (DNode *p = head; p; p = p->next) {
            cout << "Barang ke-" << i-- << ": " << "[ID " << p->data.id << "] " << p->data.nama << endl;
        }
    }

    void cetakMundur() const {
        int i = size;
        for (DNode *p = tail; p; p = p->prev)
            cout << "  " << i-- << ". [ID " << p->data.id << "] " << p->data.nama << endl;
    }
};

// STACK
struct SNode {
    Barang data;
    SNode* next;
};

class Stack {
    SNode* top;
    int count;

public: 
    Stack() : top(NULL), count(0) {}
    ~Stack() {
        while (top) {
            SNode *t = top;
            top = top->next;
            delete t;
        }
    }

    bool kosong() { 
        return count == 0; 
    }
    bool penuh() { 
        return count >= MAX_ANTRIAN; 
    }
    int jumlah() { 
        return count; 
    }

    bool push(const Barang &b) {
        if (penuh()) {
            return false;
        } 
        top = new SNode{b, top};
        count++;
        return true;
    }

    bool pop(Barang &out) {
        if (kosong()) {
            return false;
        }
        SNode *t = top;
        out = top->data;
        top = top->next;
        delete t;
        count--;
        return true;
    }

    void cetak() {
        for (SNode *p = top; p; p = p->next) {
            cout << "  - [ID " << p->data.id << "] " << p->data.nama << endl;
        }
    }
};

// HELPER INPUT
int bacaInt(const char *prompt) {
    int x;
    cout << prompt;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Input harus angka. " << prompt;
    }
    cin.ignore(10000, '\n');
    return x;
}


// MAIN FUNCTION
int main() {
    DList konveyor, histori;
    Stack antrian;
    int idBerikut = 1;
    int pilih;

    do {
        cout << "\n=== SISTEM PENGEMASAN ===" << endl;
        cout << "Konveyor: " << konveyor.jumlah()
             << " | Antrian: " << antrian.jumlah() << "/" << MAX_ANTRIAN
             << " | Histori: " << histori.jumlah() << endl;
        cout << "1. Barang masuk konveyor" << endl;
        cout << "2. Pindahkan barang dari konveyor ke antrian" << endl;
        cout << "3. Kemas barang (dari antrian ke histori)" << endl;
        cout << "4. Lihat konveyor" << endl;
        cout << "5. Lihat antrian paket" << endl;
        cout << "6. Lihat histori" << endl;
        cout << "0. Keluar" << endl;
        pilih = bacaInt("Pilih: ");

        switch (pilih) {
        case 1: {
            Barang b;
            b.id = idBerikut;
            cout << "Nama barang: ";
            cin.getline(b.nama, 50);
            int sisi = bacaInt("Masuk dari (1=depan, 2=belakang): ");
            if (sisi == 1) konveyor.pushFront(b);
            else konveyor.pushBack(b);
            cout << "Barang [ID " << b.id << "] " << b.nama << " masuk konveyor." << endl;
            idBerikut++;
            break;
        }

        case 2: {
            if (konveyor.kosong()) {
                cout << "Konveyor kosong." << endl;
            } else if (antrian.penuh()) {
                cout << "DITOLAK: antrian penuh (" << MAX_ANTRIAN << "). Barang tetap di konveyor." << endl;
            } else {
                int sisi = bacaInt("Ambil dari (1=depan, 2=belakang): ");
                Barang b;
                if (sisi == 1) konveyor.popFront(b);
                else konveyor.popBack(b);
                antrian.push(b);
                cout << "Barang [ID " << b.id << "] " << b.nama << " masuk antrian." << endl;
            }
            break;
        }

        case 3: {
            Barang b;
            if (antrian.pop(b)) {
                histori.pushBack(b);
                cout << "Barang [ID " << b.id << "] " << b.nama << " selesai dikemas." << endl;
            } else {
                cout << "Antrian kosong, tidak ada yang dikemas." << endl;
            }
            break;
        }

        case 4:
            cout << "-- Konveyor (depan ke belakang) --" << endl;
            if (konveyor.kosong()) cout << "  (kosong)" << endl;
            else konveyor.cetakMaju();
            break;

        case 5:
            cout << "-- Antrian paket --" << endl;
            if (antrian.kosong()) cout << "  (kosong)" << endl;
            else antrian.cetak();
            break;

        case 6: {
            if (histori.kosong()) {
                cout << "Histori kosong." << endl;
            } else {
                int arah = bacaInt("Telusuri (1=maju/lama ke baru, 2=mundur/baru ke lama): ");
                cout << "-- Histori --" << endl;
                if (arah == 2) histori.cetakMundur();
                else histori.cetakMaju();
            }
            break;
        }

        case 0:
            break;

        default:
            cout << "Menu tidak valid." << endl;
            break;
        }
    } while (pilih != 0);

    cout << "Selesai." << endl;
    return 0;
}