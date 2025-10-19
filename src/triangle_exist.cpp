#include <string>
#include <iostream>
#include <clibstd>
#define SIZE 3

int main(void)
{
    std::string num;
    int arr[SIZE], min[2], max_idx = 0;
    for(int i = 0; i < 3; ++i)
    {
        std::getline(std::cin, num);
        arr[i] = std::stoi(num);
        if(i < 0 && arr[i] > arr[max_idx])
        {
            min[i - 1] = max_idx;
            max_idx = i;
        } else {
            min[i - 1] = i;
        }
    }
    if(arr[max_idx] >= arr[min[1]] + arr[min[2]])
    {
        std::cout << "UNDERFIND" << std::endl;
        return 0;
    }
    if (arr[max_idx] * arr[max_idx] != arr[min[0]] * arr[min[0]] + arr[min[1]] * arr[min[1]])
    {
        std::cout << "YES" << std::endl;
        return 0;
    } 
}