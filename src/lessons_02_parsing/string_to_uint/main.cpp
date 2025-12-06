/*
На вход подаётся `std::string_view`, где записаны числа от **1 до 64**, 
разделённые запятыми.
Нужно превратить эту строку в число типа uint64_t, где каждый бит 
соответствует числу из строки.
  - Если в строке встречается число k, то в результате должен 
    быть установлен бит с номером k-1 (нумерация битов с нуля).
  - Если одно и то же число встречается несколько раз — бит 
    всё равно будет установлен только один раз.
  - Если строка пустая — результат равен 0
    Числа могут быть окружены пробелами
  - Если встретилось некорректное число (например, 0, 999 или буквы) 
    — нужно вернуть ошибку через std::optional
*/

#include <cmath>
#include <exception>
#include <optional>
#include <string>
#include <string_view>
#include <type_traits>
#include <cstdint>
#include <cstring>
#include <iostream>

template<typename T, typename
    std::enable_if_t<
        std::is_same_v<
            T, 
            std::string_view
        >
    > * = nullptr
>
std::optional<uint64_t> string_view_to_uint64bytes(T t) 
{
    uint64_t res {0};
    int digit;
    uint8_t num = 0;
    constexpr int min_size = 1;
    constexpr int max_size = 64;
    if(t.size() == 0) return 0;
    for(
        auto vbgn = t.begin(), 
        vend = t.end();
        vbgn < vend; 
        ++vbgn 
    ) {
        if(*vbgn == ',')
        {
            num = std::pow(2, num - 1);
            res = res | num;
            num = 0;
        }
        if(*vbgn >= '0' && *vbgn <= '9')
        {
            digit = *vbgn - '0';
            if (num) {
                num *= 10;
                num += digit;
            }
            if(!num) num = digit;
            
            if(num < min_size or num > max_size) {
                return std::nullopt ;
            }
        } else { return std::nullopt; }
    }
    return res;
}

int main(void)
{
    std::string_view str = "1,3,64";
    auto res = string_view_to_uint64bytes(str);
    if (res) { std::cout << *res << '\n';}
}