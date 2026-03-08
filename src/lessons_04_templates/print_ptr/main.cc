/*
Сделать функцию print_ptr(T x) которая компилируется только 
если T — указатель. 
Если передать не-указатель, компиляция должна провалиться.
*/

#include <type_traits>
#include <iostream>

template<typename T>
std::enable_if_t<std::is_pointer_v<T>, void>
print_ptr(T t) { 
    std::cout << t << '\n';
}

int main(void)
{
    int a = 233456;
    int* a_ptr = &a;
    print_ptr(a_ptr);
    
#ifdef no_ptr
    print_ptr(a);
#endif
}