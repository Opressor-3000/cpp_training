/*
Цель: 
    понять, почему перемещающий конструктор часто помечают noexcept.
Задание: 
    Сначала без noexcept — посмотри, что при перераспределении может быть копирование. 
    Затем добавь noexcept и сравни.
*/

#include <vector>
#include <iostream>
#include <utility>

struct A {
    static inline int copies=0, moves=0;
    A() = default;
    A(const A&) { ++copies; }
    A(A&&) noexcept /* попробуй без noexcept и с noexcept */ { ++moves; }
};

int main() {
    A::copies = A::moves = 0;
    std::vector<A> v;
    for (int i=0;i<100;i++) v.push_back(A{});
    std::cout << "copies=" << A::copies << " moves=" << A::moves << "\n";
}

/*
Вывод:
    если не использовать noexcept в КП то компилятор 
    будет объект тк по умолчанию перемещение может выбросить исключение

    если использовать noexcept то компилятор будет считать 
    перемещение безопасным и использовать только его 

    в сумме перемещений и копирований больше чем 100 тк 
    при заполнении выделенной памяти под вектор происходила 
    релокация на новую память 

*/
