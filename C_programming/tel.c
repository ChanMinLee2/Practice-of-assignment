#include <stdio.h>
#include <string.h>
#define MAXWORD 100

int main(int argc, char * argv)
{
    FILE *fp = fopen("data.txt", "r+t");
    char temp[MAXWORD];

    while (fscanf(fp, "%s", temp ) != EOF)
    {
        for(int index = 0; temp[index] != '\0'; index++)
        {
            if(strcmp(temp[index], ':') == 0)
            {

            }
        }
    }

}