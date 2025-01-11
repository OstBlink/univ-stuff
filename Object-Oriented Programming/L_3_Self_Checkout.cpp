#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <limits>

class Product
{
private:
    std::string name;
    double price, weight;
    int id, discount;
public:
    Product(int id, std::string name, double price, double weight, int discount) : 
    name(name), price(price), id(id), weight(weight), discount(discount) {};

    int returnId() {
        return id;
    }
    
    double returnPrice() {
        return price;
    }

    std::string returnName() {
        return name;
    }

    double returnWeight() {
        return weight;
    }

    int returnDiscount(){
        return discount;
    }

    void changeId(int i) {
        id = i;
    }

    void changeWeight(double w) {
        weight = w;
    }

    void changeName(std::string n) {
        name = n;
    }

    void changePrice(double p){
        price = p;
    }

    void changeDiscount(int d){
        discount = d;
    }
};

class Client
{
private:
    double Cash, Debut;
public:
    Client(double cash, double debut) : Cash(cash), Debut(debut) {};

    double returnCash() {
        return Cash;
    }

    double returnDebut() {
        return Debut;
    }

    void changeCash(double c) {
        Cash = c;
    }

    void changeDebut(double d) {
        Debut = d;
    }

    double returnMoney() {
        return Cash + Debut;
    }
};

std::ostream& operator<<(std::ostream& os, const Product& product) {

    Product prod = product;
    os << "Название товара: " << prod.returnName() << " - " << prod.returnPrice() << " рублей, "
       << prod.returnWeight() << " кг, Скидка: " << prod.returnDiscount() << "%";
    return os;
}


//===============================================================================================================================

Client createClient() {
    double cash, debut;
    bool fl = 1;
    while (fl) {
        std::cout << "Сколько у вас наличными? ";
        std::cin >> cash;
        if (std::cin.fail() || cash < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Пожалуйста, введите корректное значение (не меньше 0)." << std::endl;
        } else {
            fl = 0;
        }
    }

    fl = 1;
    while (fl) {
        std::cout << std::endl << "Сколько у вас на дебютовой карте? ";
        std::cin >> debut;
        if (std::cin.fail() || debut < 0) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Пожалуйста, введите корректное значение (не меньше 0)." << std::endl;
        } else {
            fl = 0;
        }
    }

    Client User(cash, debut);
    return User;
}


void printList(const std::vector<Product>& List) {
    for (size_t i = 0; i < List.size(); i++) { 
        std::cout << (i + 1) << ". " << List[i] << std::endl; 
    }
}

void printCart(std::vector<Product> Cart) {
    std::cout << "Ваша корзина: " << std::endl;
    for (size_t i = 0; i < Cart.size(); i++) {
        std::cout << (i + 1) << ". " << Cart[i] << std::endl;
    }
}

std::vector<Product> ProductListBuilder() {
    
    
    std::vector<Product> List;
    std::string line;

    std::ifstream in;
    in.open("B:\\Development\\univ-stuff\\Object-Oriented Programming\\L_3_input.txt");

    if (in.is_open()) {

            std::regex Pattern(R"(^(\d+)\s+([^\d]+)\s+([\d]+.[\d]+)\s+([\d]+.[\d]+)\s+(\d+)$)");

        while (std::getline(in, line))
        {   
            std::smatch match;
            if (std::regex_match(line, match, Pattern)) {
                try {
                    int id = std::stoi(match[1].str());
                    std::string name = match[2].str();
                    double price = std::stod(match[3].str());
                    double weight = std::stod(match[4].str());
                    int discount = std::stoi(match[5].str());

                    Product Prod(id, name, price, weight, discount);
                    if (Prod.returnDiscount() > 100) {
                        std::cerr << "[WARN] В строке используется объект неверного формата: " << line << " - " << "discount must be lower, than 101!" << std::endl; 
                    } else if (Prod.returnWeight() == 0) {
                        std::cerr << "[WARN] В строке используется объект неверного формата: " << line << " - " << "discount must be higher, than 0!" << std::endl; 
                    }
                    else {
                    List.push_back(Prod); }
                } catch (const std::invalid_argument& e) {
                    std::cerr << "[WARN] В строке используется объект неверного формата: " << line << " - " << e.what() << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cerr << "[WARN] В строке используется объект неверного размера: " << line << " - " << e.what() << std::endl;
                }
            } else {
                std::cerr << "[WARN] Какая-то строка имеет неверный формат: " << line << std::endl;
            }
        }
        in.close();
    } else {
        std::cerr << "[ERROR] Файл со списком продуктов не был открыт!" << std::endl;
    }
    return List;
}

std::vector<Product> cartFill(std::vector<Product> List) {
    
    int id;
    bool fl = 1, fl1 = 1;
    std::vector<Product> Cart;
    
    std::cout << "Список всех товаров, доступных для покупки: " << std::endl;
    while (fl1) {
        printList(List);
        std::cout << "S. Перейти в корзину" << std::endl;
        if (Cart.empty()) {
            std::cout << "Q. Закончить покупки" << std::endl;
        }
        std::cout << std::endl;
        std::cout << "Какой товар хотите приобрести? Введите номер товара (или S/Q): ";
        std::string input;
        std::cin >> input;
        
        if (input == "S" || input == "s") {
            fl1 = false;
        } else if ((input == "Q" || input == "q") && Cart.empty()) {
            exit(0);
        } else {
            try {
                id = std::stoi(input);
                if (id < 1 || id > List.size()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Пожалуйста, введите корректное значение (от 1 до " << List.size() << ")." << std::endl;
                } else {
                    Cart.push_back(List[id - 1]);
                }
            } catch (std::invalid_argument&) {
                std::cout << "Пожалуйста, введите корректное значение." << std::endl;
            }
        }
    }
    return Cart;
}

void removeFromCart(std::vector<Product>& Cart) {
    int id;
    bool fl = 1;
    while (fl) {
        printCart(Cart);
        std::cout << "Введите номер товара, который хотите удалить из корзины (0 для завершения): ";
        std::cin >> id;
        if (id == 0) {
            fl = 0;
        }
        else if (id < 1 || id > Cart.size()) {
            std::cout << "Пожалуйста, введите корректное значение (от 1 до " << Cart.size() << ")." << std::endl;
        } else {
            Cart.erase(Cart.begin() + id - 1);
            if (Cart.empty()) {
                std::cout << "Корзина пуста!" << std::endl;
                exit(0);
            }
        }
    }
}

void removeOneFromCart(std::vector<Product>& Cart, int id) {
    if (id >= 1 && id <= Cart.size()) {
        Cart.erase(Cart.begin() + id - 1);
        if (Cart.empty()) {
            std::cout << "Корзина пуста!" << std::endl;
            exit(0);
        }
    } else {
        std::cout << "Некорректный номер товара." << std::endl;
    }
    
}

void checkout(Client User, std::vector<Product> Cart) {
    double totalPrice = 0;
    for (size_t i = 0; i < Cart.size(); i++) {
        totalPrice += Cart[i].returnPrice();
    }
    std::cout << "Общая стоимость товаров в корзине: " << totalPrice << std::endl;
    if (totalPrice > User.returnCash() + User.returnDebut()) {
        std::cout << "Недостаточно средств для оплаты всех товаров! Убрать что-нибудь из корзины?" << std::endl;
        std::cout << "1. Убрать товар из корзины" << std::endl;
        std::cout << "*. Отказаться от покупок" << std::endl;
        std::string choice;
        std::cin >> choice;
        if (choice == "1") {
            removeFromCart(Cart);
        } else {
            exit(0);
        }
    } else {
        if (totalPrice < User.returnCash() && totalPrice < User.returnDebut()) {
            std::cout << "Каким способом оплатите?" << std::endl;
            
            while (true) {
                std::cout << "1. Наличными" << std::endl;
                std::cout << "2. Картой" << std::endl;
                std::cout << "*. Отказаться от покупок" << std::endl;
                std::string choice;
                std::cin >> choice;
                if (choice == "1") {
                    User.changeCash(User.returnCash() - totalPrice);
                    std::cout << "Спасибо за покупки!" << std::endl;
                    exit(0);
                } else if (choice == "2") {
                    User.changeDebut(User.returnDebut() - totalPrice);
                    std::cout << "Спасибо за покупки!" << std::endl;
                    exit(0);
                } else {
                    exit(0);
                }
            }
        } else if (totalPrice > User.returnDebut() && totalPrice < User.returnCash()) {
            User.changeCash(User.returnCash() - totalPrice);
            std::cout << "Оплата наличными прошла успешно. Спасибо за покупки!" << std::endl;
            exit(0);
        } else if (totalPrice > User.returnCash() && totalPrice < User.returnDebut()) {
            User.changeDebut(User.returnDebut() - totalPrice);
            std::cout << "Оплата картой прошла успешно. Спасибо за покупки!" << std::endl;
            exit(0);
        } else
        {   
            std::cout << "Каким способом оплатите?" << std::endl;
            
            std::cout << "1. Наличными" << std::endl;
            std::cout << "2. Картой" << std::endl;
            std::cout << "*. Отказаться от покупок" << std::endl;
            std::string choice;
            std::cin >> choice;
            if (choice == "1") {
                for (size_t i = 0; i < Cart.size(); i++)
                {
                    if (User.returnCash() > Cart[i].returnPrice()) {
                        User.changeCash(User.returnCash() - Cart[i].returnPrice());
                        removeOneFromCart(Cart, i+1);
                    } else {
                        std::cout << "Недостаточно средств для оплаты товара, переходим на другой способ оплаты! " << std::endl;
                        i = Cart.size()+1;
                    }
                }
                    
                for (size_t i = 0; i < Cart.size(); i++) {
                    if (User.returnDebut() > Cart[i].returnPrice()) {
                        User.changeDebut(User.returnDebut() - Cart[i].returnPrice());
                        removeOneFromCart(Cart, i+1);
                    } else {
                        std::cout << "Недостаточно средств для оплаты товара, оставшиеся товары удалены из корзины, спасибо за покупку! " << std::endl;
                        exit(0);
                    }
                }
            } else if (choice == "2") {
                for (size_t i = 0; i < Cart.size(); i++)
                {
                    if (User.returnDebut() > Cart[i].returnPrice()) {
                        User.changeDebut(User.returnDebut() - Cart[i].returnPrice());
                        removeOneFromCart(Cart, i+1);
                    } else {
                        std::cout << "Недостаточно средств для оплаты товара, переходим на другой способ оплаты! " << std::endl;
                        i = Cart.size()+1;
                    }
                }

                for (size_t i = 0; i < Cart.size(); i++) {
                    if (User.returnCash() > Cart[i].returnPrice()) {
                        User.changeCash(User.returnCash() - Cart[i].returnPrice());
                        removeOneFromCart(Cart, i+1);
                    } else {
                        std::cout << "Недостаточно средств для оплаты товара, оставшиеся товары удалены из корзины, спасибо за покупку! " << std::endl;
                        exit(0);
                    }
                }
            } else {
                std::cout << "До свидания!" << std::endl;
            }
        }
    }


}

//===============================================================================================================================

int main(int argc, char const *argv[])
{   

    std::vector<Product> List = ProductListBuilder();
    
    Client User = createClient();

    std::vector<Product> Cart = cartFill(List);

    checkout(User, Cart);
   
    return 0;
}

            