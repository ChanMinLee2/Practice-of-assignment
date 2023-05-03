#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int compare(const void* a, const void* b) {
    const char** str1 = (const char**) a;
    const char** str2 = (const char**) b;
    return strcmp(*str1, *str2);
}

int main(int argc, char *argv[])
{
    argv++;
    argc--;
    
    for (int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    qsort(argv, argc, sizeof(char*), compare);

    for (int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    
}