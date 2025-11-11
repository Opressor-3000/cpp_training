/*
Задание: Добавь оператор присваивания копированием и 
перемещением, инкрементируй счётчики. 
Проверь 4 кейса: 
    коп.конструктор, 
    move-конструктор, 
    коп.присваивание, 
    move-присваивание.
*/

#include <iostream>
#include <utility>

struct Counter {
    static inline int copies = 0, moves = 0;
    Counter() = default;
    Counter(const Counter& other) { ++copies; }
    Counter(Counter&&) noexcept { ++moves; }
    Counter& operator= (Counter&& other)
    {
        if(this != &other)
        {
            std::swap(copies, other.copies);
            std::swap(moves, other.moves);
            ++moves;
        }
        return *this;
    }
    Counter& operator= (const Counter& other)
    {
        if (this != &other) {
            copies = other.copies;
            moves = other.moves;
            ++copies;
        }
        return *this;
    }
};

int main() {
    Counter::copies = Counter::moves = 0;
    Counter a, d;
    Counter b = a;                // копия 
    Counter c = std::move(a);     // перемещение
    std::cout << Counter::copies << " " << Counter::moves << "\n";
}