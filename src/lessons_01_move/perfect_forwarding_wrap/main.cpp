/*
Простая обёртка с perfect forwarding
Цель: 
    сохранить категорию аргумента через std::forward.

Задание: 
    Убери std::forward и посмотри, что обе строки станут lvalue.

decltype(auto)  -  позволяет сделать вывод типа возвращаемого занчения 
                   для rvalue или lvalue выражений
*/

#include <iostream>
#include <utility>
#include <type_traits>
#include <functional>

template <class F, class... Args>
decltype(auto) call_forward(F&& f, Args&&... args) {
    return std::forward<F>(f)(std::forward<Args>(args)...);
}

template <class F, class... Args>
std::invoke_result_t<F, Args...>
call(F&& f, Args&&... args) {
    return f(args...);
}

struct Probe {
    void operator()(int&)  const { std::cout << "lvalue\n"; }
    void operator()(int&&) const { std::cout << "rvalue\n"; }
};

int main() {
    Probe p;
    Probe p1;
    int x = 0;
    int y = 1;
    call_forward(p, x);        // lvalue
    call_forward(p, 0);        // rvalue
    call(p1, y);
    call(p1, 1);
    return 0;
}
