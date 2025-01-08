#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

struct Date
{
    std::string day, month, year;
    Date(std::string day, std::string month, std::string year) : 
    day(day), month(month), year(year){};

    bool isValid() const {
        int d = stoi(day);
        int m = stoi(month);
        int y = stoi(year);
        return (d >= 1 && d <= 31) && (m >= 1 && m <= 12) && (y >= 1);
    }

    bool operator<(const Date& other) const {
        if (stoi(year) != stoi(other.year))
            return stoi(year) < stoi(other.year);
        if (stoi(month) != stoi(other.month))
            return stoi(month) < stoi(other.month);
        return stoi(day) < stoi(other.day);
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

    std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.day << "." << date.month << "." << date.year;
    return os;
    }


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

    void destroyTree(AVLNode* node) {
        if (node) {
            destroyTree(node->Left);   // Освобождаем память для левого поддерева
            destroyTree(node->Right);  // Освобождаем память для правого поддерева
            delete node;               // Освобождаем память для текущего узла
        }
    }

//Вспомогательные элементы балансировки
    
    int Height(AVLNode* Node) {
        if (Node == nullptr) return 0;
        return Node->Height;
    }

    int balanceFactor(AVLNode* Node) {
        if (Node == nullptr) return 0;
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

        if (balance > 1 && Data < Node->Left->Data)
            return RightRotate(Node);

        if (balance < -1 && Data > Node->Right->Data)
            return LeftRotate(Node);

        if (balance > 1 && Data > Node->Left->Data) {
            Node->Left = LeftRotate(Node->Left);
            return RightRotate(Node);
        }

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

    AVLNode* deleteNode(AVLNode* root, Date Data) {
        if (root ==nullptr)
        {
            return root;
        }
        
        if (Data < root->Data) 
            root->Left = deleteNode(root->Left, Data);
        else if (Data > root->Data)
            root->Right = deleteNode(root->Right, Data);
        else {
            if ((root->Left == nullptr) || (root->Right == nullptr)) {
                AVLNode* temp = root->Left ? root->Left : root->Right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                AVLNode* temp = maxValueNode(root->Right);
                root->Data = temp->Data;
                root->Right = deleteNode(root->Right, temp->Data);
            }
        }

        if (root == nullptr)
        {
            return root;
        }

        root->Height = 1 + std::max(Height(root->Left), Height(root->Right));

        int balance = balanceFactor(root);

        if (balance > 1 && balanceFactor(root->Left) >= 0)
            return RightRotate(root);

        if (balance > 1 && balanceFactor(root->Left) < 0) {
            root->Left = LeftRotate(root->Left);
            return RightRotate(root);
        }

        if (balance < -1 && balanceFactor(root->Right) <= 0)
            return LeftRotate(root);

        if (balance < -1 && balanceFactor(root->Right) > 0) {
            root->Right = RightRotate(root->Right);
            return LeftRotate(root);
        }

        return root; 
    }
    
    void inorder(AVLNode* root)
    {
        if (root != nullptr) {
            inorder(root->Left);
            std::cout << root->Data << " ";
            inorder(root->Right);
        }
    }

    void printTree(AVLNode* root, int h) {
    if (root != nullptr) {
        printTree(root->Left, h + 4);
        for (int i = 1; i <= h; ++i) {
            std::cout << " ";
        }
        std::cout << root->Data << "\n"; // Выводим только данные узла
        printTree(root->Right, h + 4);
    }
}

    bool search(AVLNode* root, Date Data)
    {
        if (root == nullptr)
            return false;
        if (root->Data == Data)
            return true;
        if (Data < root->Data)
            return search(root->Left, Data);
        return search(root->Right, Data);
    }



public:
    AVLTree() : root(nullptr) {}

    void insert(Date Data) { root = insert(root, Data); }

    void remove(Date Data) { root = deleteNode(root, Data); }

    bool search(Date Data) { return search(root, Data); }

    void destroy() {destroyTree(root);}

    AVLNode* sroot() {return root;} 

    void print() {return printTree(root, 4); }


    void printInorder()
    {
        inorder(root);
        std::cout << std::endl;
    }
};

AVLTree Building(){
    
    AVLTree Tree;
    std::string line;
    int i;

    std::ifstream in;
    in.open("B:\\Development\\univ-stuff\\Fundamental Data Structures and Algorithms\\input.txt");
    
    if (in.is_open())
    {
        std::cout << "[INFO] File opened successfully! Reading starts..." << std::endl;
        std::regex Pattern(R"((\d{1,2})[.\s/](\d{1,2})[.\s/](\d{4}))");

        while (std::getline(in, line))
        {   
            std::smatch match;
            if (std::regex_match(line, match, Pattern)) {
                Date Data(match[1].str(), match[2].str(), match[3].str());
                if (Data.isValid())
                {
                    Tree.insert(Data);
                } else {
                    std::cout << "[WARN] Data was invalid, skipping..." << std::endl;
                }
                
            } else {std::cout << "[WARN] Pattern doesn't match!" << std::endl;}
        } 
    } else
    {
        std::cout << "[ERROR] Couldn't open the file, too bad!" << std::endl;
    }
    in.close();
    std::cout << "[INFO] Reading end." << std::endl;
    return Tree;
}

int main(int argc, char const *argv[])
{
    AVLTree Tree = Building();
    Tree.printInorder();
    Tree.print();
    return 0;
}
