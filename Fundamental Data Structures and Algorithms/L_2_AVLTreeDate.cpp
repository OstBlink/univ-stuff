#include <iostream>
#include "L_1_CircularDoubleLinkedList.cpp"

struct Date
{
    int day, month, year;
    Date(int day, int month, int year) : 
    day(day), month(month), year(year) {};

    bool operator<(const Date& other) const {
        if (year != other.year)
            return year < other.year;
        if (month != other.month)
            return month < other.month;
        return day < other.day;
    }

    // Перегрузка оператора ">"
    bool operator>(const Date& other) const {
        return other < *this; 
    }

    // Перегрузка оператора "<="
    bool operator<=(const Date& other) const {
        return !(*this > other); 
    }

    // Перегрузка оператора ">="
    bool operator>=(const Date& other) const {
        return !(*this < other); 
    }

    // Перегрузка оператора "=="
    bool operator==(const Date& other) const {
        return (day == other.day) && (month == other.month) && (year == other.year);
    }

    // Перегрузка оператора "!="
    bool operator!=(const Date& other) const {
        return !(*this == other); 
    }
};


class AVLNode {
    public:
    Date Data;
    AVLNode* Left;
    AVLNode* Right;
    int Height;

    AVLNode(Date Data) : 
    Data(Data.day, Data.month, Data.year),
    Left(nullptr), Right(nullptr),
    Height(1) {}
};

class AVLTree
{
private:
    AVLNode* root;

//Вспомогательные элементы балансировки
    
    int Height(AVLNode* Node) {
        if (Node == nullptr) return;
        return Node->Height;
    }

    int balanceFactor(AVLNode* Node) {
        if (Node == nullptr) return;
        return Height(Node->Left) - Height(Node->Right);
    }

//Повороты
    
    //Правый    
    AVLNode* RightRotate(AVLNode* Node) {
        AVLNode* L = Node->Left;
        AVLNode* R = L->Right;

        L->Right = Node;
        Node->Left = R;

        Node->Height = std::max(Height(Node->Left), Height(Node->Right)) + 1;
        L->Height = std::max(Height(L->Left), Height(L->Right)) + 1;

        return L;
    }
    
    //Левый
    AVLNode* LeftRotate(AVLNode* Node) {
        AVLNode* R = Node->Right;
        AVLNode* L = R->Left;

        R->Left = Node;
        Node->Right = L;

        Node->Height = std::max(Height(Node->Left), Height(Node->Right)) + 1;
        R->Height = std::max(Height(R->Left), Height(R->Right)) + 1;

        return R;
    }

    AVLNode* insert(AVLNode* Node, Date Data) {
        if (Node == nullptr) return new AVLNode(Data);

        if (Data < Node->Data)
            Node->Left = insert(Node->Left, Data);
        else if (Data > Node->Data)
            Node->Right = insert(Node->Right, Data);
        else
            return Node;

        Node->Height = 1 + std::max(Height(Node->Left), Height(Node->Right));

        int balance = balanceFactor(Node);

        // Left Left Case
        if (balance > 1 && Data < Node->Left->Data)
            return RightRotate(Node);

        // Right Right Case
        if (balance < -1 && Data > Node->Right->Data)
            return LeftRotate(Node);

        // Left Right Case
        if (balance > 1 && Data > Node->Left->Data) {
            Node->Left = LeftRotate(Node->Left);
            return RightRotate(Node);
        }

        // Right Left Case
        if (balance < -1 && Data < Node->Right->Data) {
            Node->Right = RightRotate(Node->Right);
            return LeftRotate(Node);
        }

        return Node;
    }
    AVLNode* maxValueNode(AVLNode* Node)
    {
        AVLNode* current = Node->Left;
        while (current->Right != nullptr)
            current = current->Right;
        return current;
    }




public:
    AVLTree(/* args */);
    ~AVLTree();
};

AVLTree::AVLTree(/* args */)
{
}

AVLTree::~AVLTree()
{
}
