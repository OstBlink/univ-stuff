#include <iostream>

class AVLNode {
    public:
    int day, month, year;
    AVLNode* Left;
    AVLNode* Right;
    int Height;

    AVLNode(int day, int month, int year) : 
    day(day), month(month), year(year),
    Left(nullptr), Right(nullptr),
    Height(1) {}
};

class AVLTree
{
private:
    AVLNode* root;

//Вспомогательные элементы балансировки
    
    int height(AVLNode* Node) {
        if (Node == nullptr) return;
        return Node->Height;
    }

    int balanceFactor(AVLNode* Node) {
        if (Node == nullptr) return;
        return height(Node->Left) - height(Node->Right);
    }

//Повороты
    
    //Правый    
    AVLNode* rightRotate(AVLNode* Node) {
        AVLNode* L = Node->Left;
        AVLNode* R = L->Right;

        L->Right = Node;
        Node->Left = R;

        Node->Height = std::max(height(Node->Left), height(Node->Right)) + 1;
        L->Height = std::max(height(L->Left), height(L->Right)) + 1;

        return L;
    }
    
    //Левый
    AVLNode* leftRotate(AVLNode* Node) {
        AVLNode* R = Node->Right;
        AVLNode* L = R->Left;

        R->Left = Node;
        Node->Right = L;

        Node->Height = std::max(height(Node->Left), height(Node->Right)) + 1;
        R->Height = std::max(height(R->Left), height(R->Right)) + 1;

        return R;
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
