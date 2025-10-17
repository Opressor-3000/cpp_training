#include <stdio.h>
#include <string.h>

int validate_char(char* symb) {
    int asciis[] = {45, 46, 48, 57, 65, 90, 95, 95, 97, 122, 64, 64};
    int* ascs_ptr = asciis;
    size_t arr_sz = sizeof asciis / sizeof(int);
    for(int at = 0;*symb != '\0'; ++symb) {
        int s = (int)*symb;
        if (s == 64) ++at;
        for(int i = 0; i < arr_sz; i += 2, ++ascs_ptr) {
            if(s < *ascs_ptr || s > *++ascs_ptr || at > 1) return 0;
        }
        ascs_ptr -= arr_sz;
    }
    return 1;
}


int main(void)
{
    char str[100] = {0};
    fgets(str, sizeof(str)-1, stdin);
    char* ptr_n = strrchr(str, '\n');
    if(ptr_n != NULL)
        *ptr_n = '\0';

    char* ptr_s = str;
    if(!validate_char(ptr_s)) {
        printf("%d", 0);
        return 0;
    }
    printf("%d", 1);
    return 0;
}
