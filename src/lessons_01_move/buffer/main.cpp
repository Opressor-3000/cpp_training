/*
Цель: безопасно владеть ресурсом и корректно перемещаться.
Требования:
    Копия — глубокая.
    После перемещения источник: data == nullptr, n == 0.
    Самоприсваивание x = std::move(x) не ломает инварианты.
Ожидаемо: нет утечек, двойного delete, строки копируются корректно.

TODO: реализуй: 
    коп.конструктор, 
    коп.присваивание,
    перемещающий конструктор, 
    перемещающее присваивание (noexcept).
*/

#include <cstring>
#include <utility>

struct Buffer {
    size_t n{};
    char* data{};

    explicit Buffer(size_t n): n(n), data(new char[n]{}) {}
    Buffer (const Buffer& obj) noexcept : n(obj.n), data(new char(*obj.data)) { }
    Buffer (Buffer&& other) noexcept : n(other.n), data(other.data) {
        other.n = 0;
        other.data = nullptr;
    }
    Buffer& operator= (const Buffer& obj) {
        if (this != &obj) 
        {
            n = obj.n;
            data = obj.data;
        }
        return *this;
    }
    Buffer& operator= (Buffer&& other) {
        if(this != &other) 
        {
            std::swap(n, other.n);
            std::swap(data, other.data);
        }
        return *this;
    }
    ~Buffer() { delete[] data; }

};

int main() {
    Buffer a(8);
    std::strcpy(a.data, "hello");
    Buffer b = a;                 // копия (должна быть своя память)
    Buffer c = std::move(a);      // перемещение (забираем указатель)
};