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


int main(int argc, char * argv)
{
    FILE *fp = fopen("data.txt", "r+t");
    char temp[MAXWORD];
    tinfo tlist[MAXWORD];
    char c;
    int check_order = 0;
    int index_temp = 0; 
    int index_tlist = 0;     

    while ((c = fgetc(fp)) != EOF)
    {
        if (c == '\n')
        {
            if (temp[index_temp] == '\0')
            {
                strcpy(tlist[index_tlist++].memo, " "); 
                index_temp = 0;
            }
            
            else
            {
                strcpy(tlist[index_tlist++].memo, temp); 
                index_temp = 0;
            }
        }

        else if (c == ':')
        {
            if (check_order == 0)
            {
                strcpy(tlist[index_tlist].name, temp);
                index_temp = 0;
                temp[index_temp]='\0';
                check_order++;
            }
            
            else if (check_order == 1)
            {
                strcpy(tlist[index_tlist].phone, temp);
                index_temp = 0;
                temp[index_temp] = '\0';
                check_order--;
            }
        }

        else if (c == ' ' || c == '\t')
            ;
        
        else
        {
            temp[index_temp++] = c;
            temp[index_temp] = '\0';
        }
    }



}

