/*
std::move не снимает const
Цель: 
    понять, почему std::move(const T) не вызывает настоящий move-ctor.
Ожидаемо: 
    сработает копирование (move-ctor не принимает const W&&).
*/

#include <iostream>
#include <utility>

struct W {
    static inline int copies=0, moves=0;
    W()=default;
    W(const W&) { ++copies; }
    W(W&&) noexcept { ++moves; }
};

int main() {
    const W cw;
    W x = std::move(cw);  // какая операция сработает?
    std::cout << "copies=" << W::copies << " moves=" << W::moves << "\n";
}
/*
Сработает копирование так как объект типа const менять нельзя 
а при перемещении исходный объект поменяет свое состояние
поэтому вместо перемещения будет копирование 
*/