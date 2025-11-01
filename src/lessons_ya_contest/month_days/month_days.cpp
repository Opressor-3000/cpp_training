#include <iostream>
#include <string>

int main(void)
{
    std::string str;
    std::cin >> str;
    int month = std::stoi(str);
    std::cin >> str;
    int year = std::stoi(str);
    if( month == 2)
    {
        if(year % 4 == 0)
        {
            if( year % 100 == 0 && !(year % 400 == 0))
            {
                std::cout << 28 << std::endl;
                return 0;
            } 
            std::cout << 29 << std::endl;
            return 0;
        }
        std::cout << 28 << std::endl;
        return 0;
    }
    if (month < 9 && month != 8) {
        if (month % 2 == 0) {
            std::cout << 30 << std::endl;
            return 0;
        } else {
            std::cout << 31 << std::endl;
            return 0;
        } 
    }
    if ( month % 2 == 0 ) {
        std::cout << 31 << std::endl;
        return 0;
    } else {
        std::cout << 30 << std::endl;
        return 0;
    }
}