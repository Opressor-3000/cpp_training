#include <string>
#include <iostream>

constexpr int SIZE = 3;

int main(void)
{
    std::string num;
    int arr[SIZE];
    int min[2];
    int max_idx = 0;
    for(int i = 0; i < SIZE; ++i)
    {
        arr[i] = std::stoi(num);
        if (i > 0) 
        { 
            if(arr[i] > arr[max_idx])
            {
                min[i - 1] = max_idx;
                max_idx = i;
            } else {
                min[i - 1] = i;
            }
        }
    }
    if(arr[max_idx] >= (arr[min[0]] + arr[min[1]]))
    {
        std::cout << "UNDERFIND" << std::endl;
        return 0;
    }
    if ((arr[max_idx] * arr[max_idx]) == (arr[min[0]] * arr[min[0]] + arr[min[1]] * arr[min[1]]))
    {
        std::cout << "YES" << std::endl;
        return 0;
    } 
}