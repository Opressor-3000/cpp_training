/*
Разобраться, как устроен динамический массив «под капотом»: управление памятью,
конструирование и уничтожение объектов, корректная copy/move - семантика.
Задача «динамический массив»

Цель
Разобраться, как устроен динамический массив «под капотом»: управление памятью, конструирование и уничтожение объектов, корректная copy/move - семантика.

Требования к классу

Поведение
1. Шаблонный тип — класс должен работать с любым типом T
(в том числе с некопируемыми, если использовать move).
2. Конструктор Vector(size_t count)
— создаёт count элементов, проинициализированных значением по умолчанию (T()).
3. Copy/move семантика
- Копирующий конструктор и оператор должны создавать *глубокую копию*.
- Перемещающие — забирать владение памятью, не копируя элементы.
4. Освобождение памяти
- При уничтожении Vector должен вызывать деструкторы всех элементов и
освобождать память.
5. Безопасность по исключениям
- Если при копировании/создании элемента выбрасывается исключение — класс
должен остаться в консистентном состоянии и не должно быть утечек памяти
6. Метод at
- Проверяет индекс; если выходит за пределы size(), бросает std::out_of_range.

Ограничения реализации
- ❌ Нельзя использовать std::vector, std::unique_ptr<T[]>, std::shared_ptr, и другие готовые контейнеры.
- ✅ Можно использовать: ::operator new, ::operator delete, std::move, std::addressof, std::construct_at, std::destroy_at, placement new.
*/

#include <climits>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <cassert>
#include <type_traits>

template <typename T>
class Vector {
public:
    Vector() : Vector(MIN_SIZE / sizeof(T)) {};                        // пустой
    explicit Vector(size_t count = 0) : data_(new T[size_]), size_(count){
        if (sizeof(T) * count < MIN_SIZE) {
            count = (MIN_SIZE + sizeof(T) - 1) / sizeof(T);
        }
    };   
    
    // создать count элементов
    Vector(const Vector& other) : data_(new T[other.size_]),
        size_(other.size_), used_(other.used_) {};     // копирующий
    Vector(Vector&& other) noexcept; // перемещающий
    ~Vector(delete [] data_);

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;
    Vector& operator[](size_t idx);

    size_t size() const noexcept;    // количество элементов
    T& at(size_t index);             // доступ с проверкой границ

    // вставить элемент в конец
    void push_back(T &&t) {
        assert(used_ <= size_);
        static_assert(std::is_nothrow_move_constructible<T>::value);
        static_assert(std::is_nothrow_move_assignable<T>::value);
    }

    //
    Vector tmp(Vector& r) {

    }

    // проверяем пустой ли контейнер
    void empty() {}

    // обмен значениями
    void swap() {}

    //  текущий использованный размер контейнера
    void size() {}

    // очистить контейнер
    void clear() {}

    // получить первый элемент
    T front() {}

    // получить последний элемент
    T& back() {}

    // вернут и удалить последний элемент
    void pop() {}

    // sub vector
    Vector& subvector(size_t begin) {}
    Vector& subvector(size_t begin, size_t end) {}

private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t used_ = 0;
    static const size_t start_lenght = 100;
    static constexpr size_t MIN_SIZE = 800;
    const uint16_t resize_factor = 2;
    const size_t max_len = std::numeric_limits<uint_fast32_t>::max();
    //  написать проверку что бы if (count * sizeof(T) < 10^9 байт)
};