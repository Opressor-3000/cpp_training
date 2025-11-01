#include <iostream>
#include <string>

int main() {
    std::string result;
    char ch;

    while (std::cin.get(ch)) {
        result += ch;
    }

    std::cout << result << std::endl;
    return 0;
}