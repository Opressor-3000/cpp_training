/*
Написать шаблонную структуру has_size<T>, 
которая определяет, есть ли у типа T метод size().
*/

#include <type_traits>
#include <string>
#include <vector>

template<typename, typename = void>
struct has_size : std::false_type {};

template<typename T>
struct has_size<T, std::void_t<
    decltype(std::declval<T>().size())
    >> : std::true_type {};

int main(void)
{
    bool vector_has_size;
    vector_has_size = has_size<std::vector<int>>::value;
    bool string_has_size;
    string_has_size = has_size<std::string>::value;
    static_assert(has_size<std::vector<float>>::value);
    static_assert(!has_size<int>::value);             
    static_assert(std::is_same<has_size<std::vector<int>>::type, std::true_type>::value);
    static_assert(std::is_same<has_size<int>::type, std::false_type>::value);
}