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

std::optional<uint64_t> parse_bits(std::string_view t) noexcept
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
    return res;
}

int main(void)
{

	assert(parse_bits("") == 0);

	assert(parse_bits("1") == 1ULL << 0);
	assert(parse_bits("64") == 1ULL << 63);
	assert(parse_bits(",") == std::nullopt);
	assert(parse_bits("65") == std::nullopt);
	assert(parse_bits("999") == std::nullopt);
	assert(parse_bits("999999999999999999999999999999999") == std::nullopt);

	assert(parse_bits("1,") == std::nullopt);
	assert(parse_bits(",1") == std::nullopt);
	assert(parse_bits(",65") == std::nullopt);
	assert(parse_bits("65,") == std::nullopt);

	assert(parse_bits("1,1") == 1ULL << 0);
	assert(parse_bits("1,2") == 1ULL << 0 | 1ULL << 1);
	assert(parse_bits("2,1") == 1ULL << 0 | 1ULL << 1);

	assert(parse_bits(" ") == 0);

	assert(parse_bits(" 1") == 1ULL << 0);
	assert(parse_bits("1 ") == 1ULL << 0);

	assert(parse_bits(" 1,20") == 1ULL << 0 | 1ULL << 19);
	assert(parse_bits("1 ,20") == 1ULL << 0 | 1ULL << 19);
	assert(parse_bits("1, 20") == 1ULL << 0 | 1ULL << 19);
	assert(parse_bits("1,20 ") == 1ULL << 0 | 1ULL << 19);
    assert(parse_bits(",,9, 3 ,,  ") == (1ULL << 8) + (1ULL << 2));
    assert(parse_bits("58, 43,   0, ") == std::nullopt); 
    assert(parse_bits("14, 28, 65 ,") == std::nullopt);
    assert(parse_bits("10, 1, 100") == std::nullopt);
    assert(parse_bits(" 7 ,  ,53,, 31 ,") == (1ULL << 30) + (1ULL << 52) + (1ULL << 6));
    assert(parse_bits("") == 0);
    assert(parse_bits("o") == std::nullopt);
    assert(parse_bits("0") == std::nullopt);
}
