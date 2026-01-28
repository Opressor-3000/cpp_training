/*
На вход подаётся std::string_view, где записаны числа от 1 до 64, 
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

#include <cassert>
#include <optional>
#include <string_view>
#include <cstdint>

std::optional<uint64_t> string_view_to_uint64bits(std::string_view t) noexcept
{
    uint64_t res {0};
    uint64_t num {0};
    constexpr int min_size = 1;
    constexpr int max_size = 64;
    if(t.size() == 0) return 0;
    for(char c : t)
    {
        
        if(num && c == ',')
        {
            if(num < min_size or num > max_size) return std::nullopt;
            res |= (uint64_t{1} << (num - 1));
            num = 0;
            continue;
        }
        if(c == ' ' || c == ',') continue;
        if(c >= '0' && c <= '9')
        {
            if (num) {
                num *= 10;
                num += c - '0';
            }
            else num = c - '0';
        } else { return std::nullopt; }
    }
    if(num) 
    {
        if(num < min_size or num > max_size) return std::nullopt;
        res |= (uint64_t{1} << (num - 1));
    }
    return std::optional<uint64_t>(res);
}

int main(void)
{
    std::string_view str = "9,3,,  ", str2 = "3, 0 ,,3,45", str3 = ",, 65 ", str4 = "7,  ,53,8,31", str5 = ", 43,f, ";
    assert(string_view_to_uint64bits(str3) == std::nullopt);
    assert(string_view_to_uint64bits(str) == (1ULL << 8) + 4);
    assert(string_view_to_uint64bits(str2) == (1ULL << 44) + 4);
    assert(string_view_to_uint64bits(str4) == (1ULL << 30) + (1ULL << 52) + 128 + 64);
    assert(string_view_to_uint64bits(str5) == std::nullopt); 
}