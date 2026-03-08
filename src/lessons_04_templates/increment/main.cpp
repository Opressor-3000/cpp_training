/*
Сделать функцию increment(T x), которая:
    1. Компилируется только для целых чисел (int, long, short, и т.п.);
    2. Возвращает x + 1.
    3. Для остальных типов должна быть ошибка компиляции.
*/

#include <type_traits>

template<typename T>
requires (std::is_integral_v<T> && !std::is_same_v<T, bool>)
T increment(T x)
{
    return x + 1;
};


template <typename T>
concept incrementTest = requires(T t) 
{
    increment(t);
};

int main(void)
{
    static_assert(incrementTest<int>);
    static_assert(incrementTest<unsigned int>);
    static_assert(incrementTest<char>);
    static_assert(incrementTest<unsigned char>);
    static_assert(!incrementTest<double>);
    static_assert(!incrementTest<char[4]>);
    static_assert(!incrementTest<int*>);
    static_assert(incrementTest<unsigned long long>);

}