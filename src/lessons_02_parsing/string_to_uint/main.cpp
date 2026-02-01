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
    int64_t num {-1};
    constexpr int min_size = 1;
    constexpr int max_size = 64;
    if(t.size() == 0) return 0;
    for(char c : t)
    {
        if(c == ',' && num != -1)
        {
            if(num < min_size or num > max_size) {
                return std::nullopt;
            }
            res |= (uint64_t{1} << (num - 1));
            num = -1;
            continue;
        } 
        if(c == ' ' || c == ',') continue;
        if(c >= '0' && c <= '9') {
            if (num > 0) {
                num *= 10;
                num += c - '0';
            } else num = c - '0';
        } else { return std::nullopt; }
    }
    if(num != -1) {
        if(num < min_size or num > max_size) return std::nullopt;
        res |= (uint64_t{1} << (num - 1));
    }
    return std::optional<uint64_t>(res);
}

int main(void)
{
    assert(string_view_to_uint64bits(",,9, 3 ,,  ") == (1ULL << 8) + (1ULL << 2));
    assert(string_view_to_uint64bits("58, 43,   0, ") == std::nullopt); 
    assert(string_view_to_uint64bits("14, 28, 65 ,") == std::nullopt);
    assert(string_view_to_uint64bits("10, 1, 100") == std::nullopt);
    assert(string_view_to_uint64bits(" 7 ,  ,53,, 31 ,") == (1ULL << 30) + (1ULL << 52) + (1ULL << 6));
    assert(string_view_to_uint64bits("") == 0);
    assert(string_view_to_uint64bits("o") == std::nullopt);
    assert(string_view_to_uint64bits("0") == std::nullopt);
}
