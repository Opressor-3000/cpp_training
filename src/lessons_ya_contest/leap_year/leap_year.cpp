/*

Определите, является ли год високосным по григорианскому календарю.

Напоминание:

    год, номер которого кратен 400, — високосный;
    остальные годы, номер которых кратен 100, — невисокосные (например, годы 1700, 1800, 1900, 2100, 2200, 2300);
    остальные годы, номер которых кратен 4, — високосные.
    все остальные годы — невисокосные.

*/

#include <iostream>
#include <string>

int main(void)
{
    std::string year;
    std::getline(std::cin, year);
    int y = std::stoi(year);
    if ( y % 4 == 0){
        if (y % 100 == 0 && y % 400 != 0 )
        {
            std::cout << "NO" <<std::endl;
            return 0;
        }
        std::cout << "YES" << std::endl;
        return 0;
    } else {
        std::cout << "NO" << std::endl;
        return 0;
    }
}