#include <iostream>
#include <string>
#include <cctype>

int main(void)
{
    std::string pass;
    char ch;
    int check = 0, ascii;
    bool low = false, upp = false, dgi = false, notalnum = false;
    while(std::cin.get(ch) && ch != '\0')
    {
        ascii = int(ch);
        if(ascii < 33 || ascii > 126) {
            std::cout << "NO" << std::endl;
            return 0;
        };
        pass.push_back(ch);
        if(check >= 3) continue;
        if(!low && islower(ch)) {
            ++check;
            low = true;
            continue;
        } 
        if(!upp && isupper(ch)) {
            ++check;
            upp = true;
            continue;
        } 
        if(!dgi && isdigit(ch)) {
            ++check;
            dgi = true;
            continue;
        } 
        if(!(notalnum) && !(isalnum(ch))) {
            ++check;
            notalnum = true;
        }
    }
    if(check >= 3) {
        std::cout << "YES" << std::endl;
    } else { 
        std::cout << "NO" << std::endl; 
    }
}