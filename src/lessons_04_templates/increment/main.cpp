/*
Сделать функцию increment(T x), которая:
    1. Компилируется только для целых чисел (int, long, short, и т.п.);
    2. Возвращает x + 1.
    3. Для остальных типов должна быть ошибка компиляции.
*/

#include <utility>
#include <type_traits>

template<typename T>
struct IsSame {static constexpr bool value = false;};

template<typename T>
typename std::enable_if_t<
    std::is_integral<T>::value &&
    !std::is_same<T, unsigned char>::value &&
    !std::is_same<T, signed char>::value,
    T
>
increment(T t) { return ++t; }

int main(void)
{
    int i = 100000;
    i = increment(i);
    short s = 1000;
    long l = 11111111111;
#ifdef chars
    char c = 100;
    c = increment(c);
    unsigned char uc = 11;
    uc = increment(uc);
#elif defined(bool)
    bool t = true;
    t = increment(t);
#elif defined(enum)
    enum A {
        g = 1
    };
    A = increment(A);
#endif
}