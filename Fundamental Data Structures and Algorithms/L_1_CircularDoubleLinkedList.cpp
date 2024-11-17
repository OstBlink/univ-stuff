#include <iostream>

struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

class List {
private:
    Node* head;
    Node* tail;
public:
    List() : head(nullptr), tail(nullptr) {}

    ~List() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void print() const {
        if (!head) {
            std::cout << "List is empty." << std::endl;
            return;
        }

        Node* curr = head;
        while (curr != nullptr) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }

    void add(int value) {
        Node* nNode = new Node(value);
        if (search(value)) {
            std::cout << "This value already exists" << std::endl;
            return;
        }

        if (!head) {
            head = nNode;
            tail = nNode;
            return;
        }

        // Вставка в начало
        if (value > head->data) {
            nNode->next = head;
            head->prev = nNode;
            head = nNode;
            return;
        }

        // Вставка в конец или в середину
        Node* current = head;
        while (current->next != nullptr && current->next->data > value) {
            current = current->next;
        }

        nNode->next = current->next;
        nNode->prev = current;

        if (current->next != nullptr) {
            current->next->prev = nNode;
        } else {
            tail = nNode;
        }

        current->next = nNode;
    }

    void removeAll(int value) {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                Node* toDelete = current;
                current = current->next;

                if (toDelete->prev) {
                    toDelete->prev->next = toDelete->next;
                } else {
                    head = toDelete->next;
                }

                if (toDelete->next) {
                    toDelete->next->prev = toDelete->prev;
                } else {
                    tail = toDelete->prev;
                }

                delete toDelete;
            } else {
                current = current->next;
            }
        }
    }

    void removeBefore(int value) {
        if (!head || head->data == value) return;

        Node* current = head->next;
        while (current != nullptr && current->data != value) {
            current = current->next;
        }

        if (current) {
            Node* toDelete = current->prev;
            if (toDelete->prev) {
                toDelete->prev->next = current;
                current->prev = toDelete->prev;
            } else {
                head = current;
                current->prev = nullptr;
            }
            delete toDelete;
        }
    }

    bool search(int value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void merge(const List& other) {
        if (!other.head) return;

        Node* curr = other.head;
        while (curr != nullptr)
        {
            if (!search(curr->data)) {
                add(curr->data);
            }
            curr = curr->next;
        }
        return;
    }
};

int main(int argc, char const *argv[]) {
    List list1, list2;

    std::cout << "List 1: ";
    list1.print();

    std::cout << "List 2: ";
    list2.print();

    list1.merge(list2);

    std::cout << "Merged List: ";
    list1.print();

    list1.removeAll(20);

    std::cout << "After removing 20: ";
    list1.print();

    list1.removeAll(30);

    std::cout << "After removing 5: ";
    list1.print();

    list1.removeBefore(25);

    std::cout << "After removing before 15: ";
    list1.print();

    std::cout << "Searching for 10: " << (list1.search(10) ? "Found" : "Not Found") << std::endl;

    return 0;
}