/*
Нужно написать итератор, который умеет проходить по строке (std::string_view) 
и возвращать куски строки, разделённые заданным символом.

Условия
Разделитель — один символ.
Поддержать:
    пустые подстроки ("aa,,b" → "[aa][][b]"),
    пустую строку ("" → ""),
    разделитель в конце ("a," → "[a][]").
Итератор должен хранить только std::string_view на исходную 
строку и текущие индексы.
Не использовать std::vector, std::string или std::stringstream.
*/

#include <concepts>
#include <iterator>
#include <string_view>
#include <type_traits>
#include <cstddef>
#include <iostream>

class split_iterator {
public:
    split_iterator() = default;
    split_iterator(std::string_view str, char d) : str_(str), delimeter_(d), pos_(0) 
    {
        find_next();  
    }
    std::string_view operator*() const {
        return current_; 
    }
    split_iterator& operator++() {
        if (next_ == std::string_view::npos) {
            pos_ = std::string_view::npos;
            return *this;
        }
        pos_ = next_ + 1;
        find_next();
        return *this;
    }
    bool operator!=(const split_iterator& other) const {
        return pos_ != other.pos_;
    }
private:
    void find_next() {
        if (pos_ > str_.size()) {
            pos_ = std::string_view::npos;
            return;
        }
        next_ = str_.find(delimeter_, pos_);
        size_t end = (next_ == std::string_view::npos) ? str_.size() : next_;
        current_ = str_.substr(pos_, end - pos_);  // 
    }
    std::string_view str_{};
    std::string_view current_{};
    char delimeter_{};
    size_t pos_{ std::string_view::npos};
    size_t next_{std::string_view::npos};
};

int main(void)
{
    std::string_view s = "a,,bсd,", s1 = "";

    split_iterator it{s, ','};   // итератор на начало
    split_iterator end{};        // итератор-конец

    for (; it != end; ++it) {  
        std::cout << "[" << *it << "]"; // => [a][][bcd]
    }
    std::cout << std::endl;
    split_iterator it1{s1, ','};
    for (; it1 != end; ++it1) { // 
        std::cout << "[" << *it1 << "]";  // => []
    }
}