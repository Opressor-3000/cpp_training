/*
Сделать две версии функции describe(T):
    если T — целый тип → печатать "integral";
    если T — число с плавающей точкой → печатать "floating point".
*/

#include <concepts>
#include <iostream>
#include <utility>
#include <type_traits>
#include <string>

template<typename T> 
std::enable_if_t<
    std::is_integral_v<T> && !std::is_same_v<T, bool>, 
    void
>
describe(T) {
    std::cout << "integral" << '\n';
}

template<typename T>
std::enable_if_t<std::is_floating_point_v<T>, void>
describe(T) {
    std::cout << "floating point" << '\n';
}

template <typename T>
concept descriptive = requires(T t)
{
    { describe(t) } -> std::same_as<void>;
};


int main(void) {
    long long ll = 345678765432;
    describe(ll);
    long double ld = 1.3456760007654;
    describe(ld);
    static_assert(!descriptive<bool>);
    static_assert(!descriptive<char[4]>);
}