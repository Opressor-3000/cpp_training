/*
Самоприсваивание перемещением
Цель:
    сделать перемещающее присваивание безопасным к obj = std::move(obj)
Задание: 
    Добавь проверки инварианта «пустого» состояния: 
        если p==nullptr, объект валиден.
*/

#include <utility>

struct Box {
    int* p{};
    Box(): p(new int(7)) {}
    ~Box(){ delete p; }
    Box(Box&& other) noexcept : p(other.p) { 
        if (other.p != nullptr) other.p=nullptr;
    }
    Box& operator=(Box&& other) noexcept {
        if (this != &other) { 
            delete p; 
            p = other.p; 
            if (other.p != nullptr) other.p = nullptr; 
        }
        return *this;
    }
};

int main() {
    Box b;
    b = std::move(b);  // не должен падать/течь
}