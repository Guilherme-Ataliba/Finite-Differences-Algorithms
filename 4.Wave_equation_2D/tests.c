#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char string[100] = "diretorio/", new_num[100], new_string;
    double num = 42.2;


    sprintf(new_num, "%.2lf", num);
    strcat(string, new_num);
    printf(string);

    return 0;
}
