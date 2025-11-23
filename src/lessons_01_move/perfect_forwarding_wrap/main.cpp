/*
Простая обёртка с perfect forwarding
Цель: 
    сохранить категорию аргумента через std::forward.
Задание: 
    Убери `std::forward` и посмотри, что обе строки станут `lvalue`.
*/

#include <iostream>

template <class F, class... Args>
decltype(auto) call_forward(F&& f, Args&&... args) {
    return std::forward<F>(f)(std::forward<Args>(args)...);
}

#ifdef V1
template <class F, class... Args>
decltype(auto) call_forward(F&& f, Args&&... args) {
    return f(args...);
}
#endif

struct Probe {
    void operator()(int&)  const { std::cout << "lvalue\n"; }
    void operator()(int&&) const { std::cout << "rvalue\n"; }
};

int main() {
    Probe p;
    int x = 0;
    call_forward(p, x);        // lvalue
    call_forward(p, 0);        // rvalue
}
/*
decltype(auto)  --  позволяет сделать вывод типа возвращаемого занчения 
для rvalue или lvalue выражений
*/