#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class CircularLinkedList {
private:
    Node<T>* tail;
    int size;

public:
    CircularLinkedList() : tail(nullptr), size(0) {}

    ~CircularLinkedList() {
        while (!isEmpty()) {
            remove();
        }
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

    void add(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (isEmpty()) {
            tail = newNode;
            tail->next = tail;
        }
        else {
            newNode->next = tail->next;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void remove() {
        if (isEmpty()) {
            cout << "Список пуст. Удаление невозможно.\n";
            return;
        }
        Node<T>* head = tail->next;
        if (tail == head) {
            tail = nullptr;
        }
        else {
            tail->next = head->next;
        }
        delete head;
        size--;
    }

    void display() const {
        if (isEmpty()) {
            cout << "Список пуст.\n";
            return;
        }
        Node<T>* current = tail->next;
        do {
            cout << current->data << " ";
            current = current->next;
        } while (current != tail->next);
        cout << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    CircularLinkedList<int> list;

    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);

    cout << "Элементы списка: ";
    list.display();

    list.remove();
    cout << "После удаления одного элемента: ";
    list.display();

    return 0;
}