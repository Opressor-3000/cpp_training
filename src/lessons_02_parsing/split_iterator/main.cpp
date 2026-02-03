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
#include <cassert>
#include <sstream>
#include <string>

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
        if (!str_.size() || pos_ > str_.size() ) {
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


bool test(std::string_view input, std::string_view expected )
{
	split_iterator it (input, ',');
    split_iterator end{};
	std::stringstream ss;
	for (; it != end; ++it) {
		ss << "[" << *it << "]";
	}
	std::string actual_output = ss.str();

	return actual_output == expected;
}

int main(void)
{
    assert(test("", ""));
	assert(test("a", "[a]"));
	assert(test("a,", "[a][]"));
	assert(test(",a", "[][a]"));
	assert(test("a,b", "[a][b]"));
	assert(test("a,b,c,", "[a][b][c][]"));
	assert(test("a,,b,", "[a][][b][]"));
	assert(test("a,,b,,c,", "[a][][b][][c][]"));
	assert(test("abc", "[abc]"));
	assert(test("abc,a", "[abc][a]"));
	assert(test("ac,abc,de", "[ac][abc][de]"));

}