/*
Цель: 
    понять, почему перемещающий конструктор часто помечают noexcept.
Задание: 
    Сначала без noexcept — посмотри, что при перераспределении может быть копирование. 
    Затем добавь noexcept и сравни.
*/

#include <vector>
#include <iostream>

struct A {
    static inline int copies=0, moves=0;
    A() = default;
    A(const A&) { ++copies; }
    A(A&&) /* попробуй без noexcept и с noexcept */ { ++moves; }
};

int main() {
    A::copies = A::moves = 0;
    std::vector<A> v;
    for (int i=0;i<100;i++) v.push_back(A{});
    std::cout << "copies=" << A::copies << " moves=" << A::moves << "\n";
}
