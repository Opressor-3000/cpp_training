#include <iostream>
#include <utility>

struct Counter {
    static inline int copies = 0, moves = 0;
    Counter() = default;
    Counter(const Counter&) { ++copies; }
    Counter(Counter&&) noexcept { ++moves; }
};

int main() {
    Counter::copies = Counter::moves = 0;
    Counter a;
    Counter b = a;                // копия
    Counter c = std::move(a);     // перемещение
    std::cout << Counter::copies << " " << Counter::moves << "\n";
}