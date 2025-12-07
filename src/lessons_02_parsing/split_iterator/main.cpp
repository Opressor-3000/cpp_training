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

#include <string_view>
#include <type_traits>
#include <cstddef>
#include <iostream>

template <typename T, typename S>
class split_iterator {
    T& str_;          
    S delimiter_;     
    size_t pos_; 
    size_t npos_;
    std::string_view current_;
public:
    split_iterator() : str_{""}, pos_{std::string_view::npos} {}
    split_iterator(T& str, S delimiter)
    : str_(str), delimiter_(delimiter), pos_(0) 
    {
        skip_delimiter();
    }

    void skip_delimiter() 
    {
        while (pos_ < str_.size() && str_[pos_] == delimiter_) 
        {
            ++pos_;
        }
    }
    split_iterator& operator++() 
    {
        find_();
        return *this;
    }

    auto operator*() const 
    {
        return current_;
    }

    bool operator!=(const split_iterator& other) const
    {
        return pos_ != other.pos_;
    }

    std::ostream& operator<<(std::ostream &ost, const auto &itr) 
    {
        return ost << *itr;
    }
private:
    void find_() 
    {
        if(pos_ == std::string::npos)
        {
            str_ = "";
            return;
        }
        size_t next_pos = str_.find(delimiter_, pos_);
        if(next_pos == std::string_view::npos) {
            str_ = str_.substr(pos_);
            pos_ = std::string_view::npos;
        } else {
            str_ = str_.substr(pos_, next_pos - pos_);
            pos_ = next_pos + 1;
        }
    }
};


int main(void)
{
    std::string_view s = "a,,bсd,";

    split_iterator it{s, ','};   // итератор на начало
    split_iterator end{};        // итератор-конец

    for (; it != end; ++it) {
        std::cout << "[" << *it << "]";
    }
}