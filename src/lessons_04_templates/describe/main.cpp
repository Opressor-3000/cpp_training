/*
Сделать две версии функции describe(T):
    если T — целый тип → печатать "integral";
    если T — число с плавающей точкой → печатать "floating point".
*/

#include <iostream>
#include <utility>
#include <type_traits>
#include <string>

template<typename T> 
std::enable_if_t<std::is_integral_v<T>, void>
describe(T) {
    std::cout << "integral" << '\n';
}

template<typename T>
std::enable_if_t<std::is_floating_point_v<T>, void>
describe(T) {
    std::cout << "floating point" << '\n';
}

int main(void) {
    long long ll = 345678765432;
    describe(ll);
    long double ld = 1.3456760007654;
    describe(ld);
    #ifdef disabled 
    std::string str = "dfghjk";
    describe(str);
    #endif
}