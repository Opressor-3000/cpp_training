#include <iostream>

int id(const int&)       { std::cout << "const&\n"; return 1; }
int id(int&&)            { std::cout << "&&\n";     return 2; }

int main() {
    int x = 10;
    id(5);        //  5 is a literal that is not allocated in memory, so it is rvalue
    id(x);        // x is lvalue return const&
    id(std::move(x)); // function call a static_cast to T&& is xvalue  
    id(x + 1);    // this expretion is not allocated in mamory - pure rvalue category 
}