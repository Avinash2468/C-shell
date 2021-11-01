#include "headers.h"

void print_prompt(int check)
{
    printf("\033[0;31m");
    if (check == 0)
    {
        printf("\navinashell>");  
    }
    else
    {
        printf("avinashell>");
    }
    printf("\033[0m");
}