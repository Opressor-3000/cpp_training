#include <iostream>
#include <string>
#include <cstdlib> 


int main(void)
{
    int arr[4];
    std::string str; 
    for(int i = 0; i < 4; ++i) {
        std::getline(std::cin, str);
        arr[i] = std::stoi(str);
    }
    for(int i = 0; i < 4; ++i) {
        std::cout << arr[i] << '\n';
    }
    std::cout << abs(arr[0] - arr[2]) << "  " << abs(arr[1] - arr[3]) << '\n';
    if (arr[0] == arr[2] || arr[1] == arr[3] || abs(arr[0] - arr[2]) == abs(arr[1] - arr[3]))
    {
        std::cout << "YES" << std::endl;
    } else { std::cout << "NO" << std::endl; }
}

