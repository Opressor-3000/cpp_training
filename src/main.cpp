#include <string>
#include <iostream>

using std::string;


int main(void) 
{
    string  str;

    std::cout << str << std::endl;
    getline(std::cin, str);
    if(str.empty()) {
        std::cout << "faile";
        abort(); 
    }
    std::cout << str << std::endl;
    return 0;
}