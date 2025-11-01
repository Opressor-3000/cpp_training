#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string str;
    std::getline(std::cin, str);
    std::istringstream iss(str);
    int number, sum = 0;

    while (iss >> number) {
        sum += number;
    }

    std::cout << sum << std::endl;
    return 0;
}