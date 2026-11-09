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
        DNode* n = new DNode{b, head, NULL};
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
        for (DNode *p = tail; p; p = p->prev) {
            cout << "Barang ke-" << i-- << ": " << "[ID " << p->data.id << "] " << p->data.nama << endl;
        }
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

}