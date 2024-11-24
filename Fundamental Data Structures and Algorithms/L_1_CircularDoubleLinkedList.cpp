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
        std::cout << head->data << " "<< tail -> data << std::endl;
    }

    void add(int value) {
        Node* nNode = new Node(value);

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
            tail = nNode->next;
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
    if (!head || !head->next) return; 

    if (head->data == value){
            Node* toDelete = tail;
            if (tail) {
                tail = tail->prev;
                if (tail) {
                    tail->next = nullptr;
                } else {
                    head = nullptr; 
                }
                delete toDelete;
            }
        }

    Node* current = head->next; 
    while (current != nullptr) {
        
        if (current->data == value) { 
            Node* toDelete = current->prev; 

            if (toDelete) { 
                if (toDelete->prev) { 
                    toDelete->prev->next = current;
                    current->prev = toDelete->prev;
                } else {
                    head = current;
                    current->prev = nullptr;
                }
                delete toDelete;
                current = current->next; 
            } else {
                current = current->next; 
            }
        } else {
            current = current->next; 
        }
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
            add(curr->data);
            curr = curr->next;
        }
        return;
    }

    void BTask(int max, int value) {
        if (max == 0) {
            std::cout << "Max can't be 0" << std::endl;
            return;
        }

        if (max < 0 && value >= 0){
            std::cout << "Max and value must be positive or negative at the same time" << std::endl;
            return;
        }

        int k = value / max;
        if (k == 0) {
            add(value);
            return;
        } else {
            for (int i = 0; i < k; i++)
            {
                add(max);
            }
            if (value - max * k != 0)
            {
                add(value - max * k);
            }
            return;
        };
        return;
    }
};

int main(int argc, char const *argv[]) {
    List list1, list2;
    list1.add(1);
    list1.add(1);
    list1.add(2);
    list1.add(2);
    list1.add(2);
    list1.add(4);
    list1.add(5);
    list1.add(5);

    list2.add(0);
    list2.add(1);
    list2.add(4);
    list2.add(5);

    std::cout << "List 1: ";
    list1.print();

    std::cout << "List 2: ";
    list2.print();

    list1.merge(list2);

    std::cout << "Merged List: ";
    list1.print();

    list1.removeAll(5);

    std::cout << "After removing 5: ";
    list1.print();

    list1.removeBefore(4);

    std::cout << "After removing before 4: ";
    list1.print();

    list1.removeBefore(25);

    std::cout << "After removing before 25: ";
    list1.print();

    std::cout << "Searching for 10: " << (list1.search(10) ? "Found" : "Not Found") << std::endl;

    // List List1;
    // int max, num;
    // std::cout << "Enter max and value: ";
    // std::cin >> max >> num;

    // List1.BTask(max, num);
    // List1.print();
    // return 0;
}