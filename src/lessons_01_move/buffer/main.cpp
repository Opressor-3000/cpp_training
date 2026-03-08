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

#include <concepts>
#include <cstring>
#include <utility>
#include <cstddef>

struct Buffer {
    size_t n{};
    char* data{};
public:
    explicit Buffer(size_t n): n(n), data(new char[n]{}) {}

    Buffer (const Buffer& obj): Buffer{obj.n} {
        std::memcpy(data, obj.data, n);
    }

    Buffer (Buffer&& other) noexcept : n(other.n), data(other.data) {
        other.n = 0;
        other.data = nullptr;
    }

    Buffer& operator= (const Buffer& obj) {
        
        Buffer copy { obj };
        swap(copy);
        return *this;
    }

    Buffer& operator= (Buffer&& other) noexcept {
        if(this != &other) 
        {
            delete[] data;
            n = other.n;
            data = other.data;
            other.data = nullptr;
            other.n = 0;
        }
        return *this;
    }

    void swap(Buffer& other) noexcept
    {
        std::swap(n, other.n);
        std::swap(data, other.data);
    }

    ~Buffer() { delete[] data; }
};

int main() {
    Buffer a(8);
    std::strcpy(a.data, "hello");
    Buffer b = a;                 // копия (должна быть своя память)
    Buffer c = std::move(a);      // перемещение (забираем указатель)
};