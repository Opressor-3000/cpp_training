/*
Цель: 
    увидеть, что лишний std::move может помешать RVO/NRVO.
Ожидаемо: 
    `make_ok` даёт 0 или 1 move (зависит от компилятора/флагов), 
    `make_bad` — как минимум 1 move.
*/

#include <iostream>
#include <utility>

struct Tr {
    static inline int moves=0;
    Tr() = default;
    Tr(Tr&&){ ++moves; }
};

Tr make_ok() {
    Tr t;
    return t;         // RVO/NRVO возможен
}
Tr make_bad() {
    Tr t;
    return std::move(t); // заставляет перемещение
}

int main(){
    Tr::moves = 0;
    Tr a = make_ok(); // NRVO создаст объект на месте без вызова конструктора
    std::cout << "moves after ok: " << Tr::moves << "\n";

    Tr::moves = 0;
    Tr b = make_bad();  // не будет применен NRVO тк явно используется move
    std::cout << "moves after bad: " << Tr::moves << "\n";
}
