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
#include <queue>
#include <sstream>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <algorithm>

// using Placement New
template <typename T> 
void construct(T *p, const T &other) { new (p) T(other); }

template <typename T> 
void construct(T *p, T &&other) { new (p) T(std::move(other)); }

template <typename T>
class Vector {
public:
    // default 
    Vector() {};        

    // создать count элементов
    explicit Vector(size_t count) : 
    data_(new T[calc_size(count)]),
    size_(calc_size(count)),
    used_(calc_size(count)) {};

    // копирующий
    Vector(const Vector& other) : data_(new T[other.size_]),
    size_(other.size_), used_(other.used_) {
        for(size_t i = 0; i < used_; ++i) construct(data_ + i, other.data_[i]);
    };     
    
    // перемещающий
    Vector(Vector&& other) noexcept : 
    size_(other.size_), used_(other.used_) {
        data_ = other.data_;
        other.size_ = 0;
        other.used_ = 0;
        other.data_ = nullptr;
    }; 

    // destructor
    ~Vector() {delete[] data_; };

    Vector& operator=(const Vector& other) {
        Vector tmp(other);
        std::swap(*this, tmp);
        return *this;
    };

    //
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            used_ = other.used_;
        }
        return *this;
    };

    T& at(size_t index)              // доступ с проверкой границ
    {
        if(index >= used_) throw std::out_of_range("index out fo range");
        return data_[index];
    }

    T& operator[](size_t index) {
        assert(index < used_);
        return data_[index];
    }

    const T& operator[](size_t index) const { return data_[index];}

    size_t size() const noexcept { return size_;};    // количество элементов

    // вставить элемент в конец lvalue ссылке
    void push(const T& t) {
        static_assert(std::is_same<std::decay_t<decltype(t)>, T>::value,
                    "MyVector<T> only accepts objects of exact type T");
        if (used_ == size_) resize();
        data_[used_++] = t;
    }

    // вставить элемент в конец rvalue ссылке
    void push(T&& t) {
        static_assert(std::is_same<std::decay_t<decltype(t)>, T>::value,
                    "MyVector<T> only accepts objects of exact type T");
        static_assert(std::is_nothrow_move_constructible<T>::value,
                    "The type has a non-throwing move constructor.");
        static_assert(std::is_nothrow_move_assignable<T>::value,
                    "The type has a non-throwing move assignment operator.");
        if (used_ == size_) resize();
        construct(data_ + used_, std::move(t));
        ++used_;
    }

    void resize()
    {
        resize_internal(this->size_ * this->resize_factor);
    }

    void resize(size_t size_new) {resize_internal(size_new);}

    // проверяем пустой ли контейнер
    bool empty() const noexcept { return used_ == 0; }

    // обмен значениями
    void swap() {}

    // очистить контейнер
    void clear() {
        for(size_t i = 0; i < size_; ++i) data_[i].~T();
        used_ = 0;
    }

    // получить первый элемент
    T& front() {
        assert(used_ > 0);
        return data_[0];
    }

    // получить последний элемент
    T& back() {
        assert(used_ > 0);
        return data_[size_ - 1];
    }

    // вернут и удалить последний элемент
    void pop() {
        assert(used_ > 0);
        data_[used_].~T();
        --size_;
    }

    // sub vector
    Vector subvector(size_t begin) const {
        if (used_ < begin) throw std::out_of_range("index out of range");
        size_t dlt = used_ - begin;
        Vector other(dlt);
        for (size_t i = begin, j = 0; i < size_; ++i) {
            construct(other.data_ + i, data_[begin + i]);
        }
        return other;
    }

    Vector subvector(size_t begin, size_t end) const {
        if (begin > end or used_ > end) throw std::out_of_range("index out of range");
        size_t new_sz = end - begin;
        Vector other(end - begin);
        for(size_t i = begin; i > new_sz; ++i) {
            construct(other.data_ + i, data_[begin + i]);
        }
        return other;
    }

private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t used_ = 0;
    static const uint32_t max_byte = 1000000000U; 
    static constexpr size_t MIN_SIZE = 800;
    const uint16_t resize_factor = 2;
    //  написать проверку что бы if (count * sizeof(T) < 10^9 байт)
    void resize_internal(size_t size_new)
    {
        if(size_new <= size_)
            return;
        while(size_ < size_new) {
            size_ *= resize_factor;
        }
        T *p = new T[size_];
        for(size_t i = 0; i < used_; ++i) {
            construct(p + i, std::move(data_[i]));
        }
        delete[] data_;
        data_ = p;
    }

    static size_t calc_size(size_t requir_sz) {
        if (sizeof(T) == 0) return 0;
        size_t min_elements = (MIN_SIZE + sizeof(T) - 1) / sizeof(T);
        return std::max(requir_sz, min_elements);
    }
};

int main (void)
{
    Vector<float> v;

}