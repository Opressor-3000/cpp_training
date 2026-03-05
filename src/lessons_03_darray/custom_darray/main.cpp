/* 
Разобраться, как устроен динамический массив «под капотом»: управление памятью,
конструирование и уничтожение объектов, корректная copy/move - семантика.
Задача «динамический массив»

Цель
Разобраться, как устроен динамический массив «под капотом»: управление памятью, 
конструирование и уничтожение объектов, корректная copy/move - семантика.

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


template <typename T> 
void construct(T *p, const T &other) { new (p) T(other); }

template <typename T> 
void construct(T *p, T &&other) { new (p) T(std::move(other)); }

template <typename T>
class Vector {
public:
    Vector() {};        

    // создать count элементов
    explicit Vector(size_t count) : 
    size_(calc_size(count)),
    data_(static_cast<T*>(::operator new(sizeof(T) * size_))),
    used_(calc_size(count)) {
        for (size_t i = 0; i < used_; ++i)
            new (data_ + i) T(); 
    };

    // копирующий
    Vector(const Vector& other) : 
      size_(other.size_),
      data_(nullptr),
      used_(other.used_) 
    {
        try {
            data_ = static_cast<T*>(::operator new(sizeof(T) * size_));
            for(size_t i = 0; i < used_; ++i) construct(data_ + i, other.data_[i]);
        } catch (...) {
            destroy();
            throw;
        }
    };     
    
    // перемещающий
    Vector(Vector&& other) noexcept : 
      size_(other.size_), 
      data_(other.data_),
      used_(other.used_)
    {
        other.size_ = 0;
        other.data_ = nullptr;
        other.used_ = 0;
    }; 

    // destructor
    ~Vector() {
        destroy();
    }
    // копирование присваиванием
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector tmp(other);
            std::swap(*this, tmp);
        }
        return *this;
    };

    // перемещение присваиванием
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            destroy();
            size_ = other.size_;
            data_ = other.data_;
            used_ = other.used_;
            other.size_ = 0;
            other.data_ = nullptr;
            other.used_ = 0;
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

    size_t size() const noexcept { return used_;};   

    // вставить элемент в конец по lvalue ссылке
    void push(const T& t) {
        static_assert(std::is_same<std::decay_t<decltype(t)>, T>::value,
                    "MyVector<T> only accepts objects of exact type T");
        if (used_ == size_) resize();
        construct(data_ + used_, t);
    }

    // вставить элемент в конец по rvalue ссылке
    void push(T&& t) {
        static_assert(std::is_same<std::decay_t<decltype(t)>, T>::value,
                    "MyVector<T> only accepts objects of exact type T");
        static_assert(std::is_nothrow_move_constructible<T>::value,
                    "The type has a non-throwing move constructor.");
        static_assert(std::is_nothrow_move_assignable<T>::value,
                    "The type has a non-throwing move assignment operator.");
        if (used_ == size_) resize();
        try {
            construct(data_ + used_, std::move(t));
            ++used_;
        } catch (...) {
            throw;
        }
    }

    void resize()
    {
        resize_internal(this->size_ * this->resize_factor);
    }

    void resize(size_t new_size) {resize_internal(new_size);}

    // проверяем пустой ли контейнер
    bool empty() const noexcept { return used_ == 0; }

    // очистить контейнер
    void clear() {
        for(size_t i = 0; i < used_; ++i) data_[i].~T();
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
        return data_[used_ - 1];
    }

    // вернут и удалить последний элемент
    void pop() {
        assert(used_ > 0);
        --used_;
        data_[used_].~T();
    }

    // создаем vector из subvector
    Vector subvector(size_t begin) const {
        if (begin >= used_) throw std::out_of_range("index out of range");
        size_t dlt = used_ - begin + 1;
        Vector other(dlt);
        for (size_t i = 0; i < dlt; ++i) {
            construct(other.data_ + i, data_[begin + i]);
        }
        return other;
    }

    Vector subvector(size_t begin, size_t end) const {
        if (begin > end or used_ > end) throw std::out_of_range("index out of range");
        size_t new_sz = end - begin;
        Vector other(end - begin);
        for(size_t i = begin; i < new_sz; ++i) {
            construct(other.data_ + i, data_[begin + i]);
        }
        return other;
    }

private:
    size_t size_ = 0;
    T* data_ = nullptr;
    size_t used_ = 0;
    static const uint32_t max_byte = (1UL << 32) - 1; 
    static constexpr size_t MIN_SIZE = 800;
    const uint16_t resize_factor = 2;

    //  написать проверку что бы if (count * sizeof(T) < 10^9 байт)
    void resize_internal(size_t new_size)
    {
        if(new_size <= size_) return;
        if (new_size > max_byte) size_ = max_byte;
        else while(size_ < new_size) {
            size_ *= resize_factor;
        }
        T* p = static_cast<T*>(::operator new(sizeof(T) * size_));
        try {
            for(size_t i = 0; i < used_; ++i) {
                construct(p + i, std::move(data_[i]));
            }
        } catch (...) {
            delete[] p;
            throw;
        }
        destroy();
        data_ = p;
    }

    static size_t calc_size(size_t requir_sz) {
        if (sizeof(T) == 0) return 0;
        size_t min_elements = (MIN_SIZE + sizeof(T) - 1) / sizeof(T);
        return std::max(requir_sz, min_elements);
    }

    void destroy() noexcept {
        for (size_t i = 0; i < used_; ++i)
            data_[i].~T(); // вручную вызываем деструкторы
        ::operator delete(data_); // освобождаем сырую память
        data_ = nullptr;
        used_ = 0;
        size_ = 0;
    }
};

struct TestObject {
    static int ctor;
    static int copy_ctor;
    static int move_ctor;
    static int dtor;

    int value;

    TestObject(int v = 0) : value(v) { ++ctor; }

    TestObject(const TestObject& other) : value(other.value) {
        ++copy_ctor;
    }

    TestObject(TestObject&& other) noexcept : value(other.value) {
        ++move_ctor;
        other.value = -1;
    }

    TestObject& operator=(const TestObject& other) {
        if (this != &other) {
            value = other.value;
        }
        return *this;
    }

    TestObject& operator=(TestObject&& other) noexcept {
        if (this != &other) {
            *this = std::move(other);
        }
        return *this;
    }

    ~TestObject() { ++dtor; }

    static void reset() {
        ctor = copy_ctor = move_ctor = dtor = 0;
    }
};

int TestObject::ctor = 0;
int TestObject::copy_ctor = 0;
int TestObject::move_ctor = 0;
int TestObject::dtor = 0;

void test_subvector() {
    Vector<int> v(5);

    for (int i = 0; i < 5; ++i)
        v[i] = i;

    Vector<int> sub = v.subvector(2);

    assert(sub[0] == 2);
    assert(sub[1] == 3);
    assert(sub[2] == 4);
}

void test_destruction() {
    TestObject::reset();
    {
        Vector<TestObject> v(3);
    }
    assert(TestObject::ctor == TestObject::dtor);
}

void test_out_of_range() {
    Vector<int> v(2);
    bool thrown = false;

    try {
        v.at(100);
    } catch (const std::out_of_range&) {
        thrown = true;
    }

    assert(thrown);
}

void test_resize() {
    Vector<int> v(2);

    v.push(1);
    v.push(2);
    v.push(3); // должен вызвать resize

    assert(v[2] == 3);
}

void test_move_assignment() {
    Vector<int> v1(2);
    v1[0] = 100;

    Vector<int> v2(1);
    v2 = std::move(v1);

    assert(v2[0] == 100);
}

void test_copy_assignment() {
    Vector<int> v1(2);
    v1[0] = 10;
    v1[1] = 20;

    Vector<int> v2(2);
    v2 = v1;

    assert(v2[0] == 10);
    assert(v2[1] == 20);
}

void test_move_constructor() {
    TestObject::reset();

    Vector<TestObject> v(2);
    v[0] = TestObject(5);

    Vector<TestObject> moved(std::move(v));

    assert(moved[0].value == 5);
}

void test_copy_constructor() {
    TestObject::reset();

    Vector<TestObject> v(2);
    v[0] = TestObject(10);
    v[1] = TestObject(20);

    Vector<TestObject> copy(v);

    assert(copy[0].value == 10);
    assert(copy[1].value == 20);
}

void test_push_and_access() {
    Vector<int> v(2);

    v.push(1);
    v.push(2);

    assert(v[0] == 1);
    assert(v[1] == 2);
}

void test_basic_creation() {
    Vector<int> v(10);
    assert(v.size() >= 10);
    assert(!v.empty());
}


int main (void)
{
    test_basic_creation();
    test_copy_assignment();
    test_destruction();
    test_copy_constructor();
    test_move_constructor();
    test_move_assignment();
    test_out_of_range();
    test_push_and_access();
    test_resize(); 
    test_subvector();
    return 0;
}