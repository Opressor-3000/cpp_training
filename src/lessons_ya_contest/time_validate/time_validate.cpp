#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
    int hh, mm, ss;
    char hhc, mmc, ssc;
    scanf("%d %d %d", &hh, &mm, &ss);
    char time_[10] = {0};
    char* ptr_time = time_;
    const char format[] = "%d";
    if(hh < 0 || hh > 23) {
        strcat(ptr_time, "--:");
        ptr_time += 3;
    } else { 
        sprintf(ptr_time, format, hh);
        ptr_time += 3;
    }
    if(mm < 0 || mm > 59) {
        strcat(ptr_time, "--:");
        ptr_time += 3;
    } else {
        sprintf(ptr_time, format, mm);
        ptr_time += 3;
    }
    if(ss < 0 || ss > 59) {
        strcat(ptr_time, "--");
    } else { 
        sprintf(ptr_time, format, ss);
    }     
    printf("%s", time_);
    return 0;
}

