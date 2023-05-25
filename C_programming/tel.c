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

    if (argv[0] == "-a") // add option operate
    {
        
    }

    else if (argv[0] == "-d") // delete option operate
    {
        /* code */
    }
    
    else if (argv[0] == "-l") // list option oprate
    {
        /* code */
    }

    else if (argc > 0) // search type oprate
    {
        char keyword[] = argv[0] 
    }
    

    else if (argc == 0) // manual type oprate
    {
        printf(" 1. how to input\n");
        printf(" : ./tel [-adl] words \n\n");
        printf(" 2. what is option\n");
        printf(" : each options are oprated indepently");
        printf(" thus, their can't be used together in one time \n\n");
        printf(" 2-0. manual -- no option, no input words\n");
        printf(" : ex) ./tel \n");
        printf(" : it can print manual for this tel program \n\n");
        printf(" 2-1. search -- no option, but words input exists \n");
        printf(" : ex) ./tel words \n");
        printf(" : it can search the info as keyword, in list of tel \n\n");
        printf(" 2-2. add option\n");
        printf(" : ex) ./tel -a words \n");
        printf(" : it can add new info to list of tel \n\n");
        printf(" 2-3. delete option\n");
        printf(" : ex) ./tel -d words \n");
        printf(" : it can delete selected info in list of tel \n\n");
        printf(" 2-4. list option\n");
        printf(" : ex) ./tel - l words \n");
        printf(" : it can print every elements in list of tel \n\n");
    }
    
    return 0;
}

