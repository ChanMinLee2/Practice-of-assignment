#include <stdio.h>
#include <string.h>
#define MAXWORD 1000

typedef struct tinfo tinfo; 
struct tinfo
{
    char name[30];
    char phone[20];
    char memo[40];
};

tinfo tlist[MAXWORD];

int main(int argc, char * argv)
{
    FILE *fp = fopen("data.txt", "r+t");
    char temp[MAXWORD];  
    int check = 0;
    char * temp_fp;
    int index_tlist = 0;

    while(fscanf(fp,"%s",temp) != EOF)
    {
        char * temp_fp = temp;
        strtok(temp,":");
        while (temp_fp != NULL)
        {
            printf("%s\n", temp_fp);
            if (check == 0)
            {
                strcpy(tlist[index_tlist].name, temp_fp);
                check++;
            }
            
            else if (check == 1)
            { 
                strcpy(tlist[index_tlist].phone, temp_fp);
                check++;
            }
            
            else if (check == 2)
            {
                strcpy(tlist[index_tlist++].memo, temp_fp);
                check++;
            }
            temp_fp = strtok(NULL, ":"); 
        }
        if (temp_fp == NULL)
        {
            check == 0;
        }
        
    }
    temp_fp = strtok(temp, ":"); 
    
    printf("%s %s %s\n", tlist[0].name, tlist[0].phone, tlist[0].memo);    

    argv++;
    argc--;

    if (argv[0] == "-d")
    {
        /* code */
    }

    else if (argv[0] == "-a")
    {
        /* code */
    }
    
    else if (argv[0] == "-l")
    {
        /* code */
    }
    

    return 0;
}

