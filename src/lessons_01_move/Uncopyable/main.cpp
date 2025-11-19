/*
Цель: понять удаление копирования и сохранение перемещения
Добавь std::vector<Token> v; v.push_back(Token{}); 
— убедись, что это работает благодаря move.
*/
#include <vector>

struct Token {
    int* p{new int(42)};
    Token() = default;
    ~Token(){ delete p; }

    Token(const Token&) = delete;
    Token& operator=(const Token&) = delete;

    Token(Token&& other) noexcept : p(other.p) { other.p = nullptr; }
    Token& operator=(Token&& other) noexcept {
        if (this != &other) { delete p; p = other.p; other.p = nullptr; }
        return *this;
    }
};

int main() {
    Token a = Token{};           // ок
    // Token b = a;                  // должно НЕ компилироваться (проверь)
    std::vector<Token> v;
    v.push_back(Token{});
}
