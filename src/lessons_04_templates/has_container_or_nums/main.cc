/*
Сделать функцию describe(T x), которая:
    работает, если T — контейнер (есть begin() и end());
    работает, если T — арифметический тип (int, double и т.д.);
    работает, если T — контейнер (есть begin() и end());
*/

#include <deque>
#include <type_traits>
#include <vector>
#include <iterator>

template<typename T, typename = void>
struct has_iterators : std::false_type {};

template<typename T>
struct has_iterators<T,
    std::void_t<
        decltype(begin(std::declval<T>())),
        decltype(end(std::declval<T>()))
>> : std::true_type {};

template<
    typename T, 
    typename std::enable_if_t<has_iterators<T>::value, int> = 0
>
constexpr std::true_type describe() { return {}; }

template <
    typename T,
    typename std::enable_if_t<std::is_arithmetic_v<T>, int> = 0
>
constexpr std::true_type describe() { return {}; }

int main (void)
{
    static_assert(describe<int>() );
    static_assert(describe<std::deque<int>>());
}



