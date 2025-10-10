#include <string>
#include <iostream>

using std::string;


int main(void) 
{
    string str;
    getline(std::cin, str);
    std::cout << str << std::endl;
    return 0;
}