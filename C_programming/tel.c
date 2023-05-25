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
int index_tlist = 0;

int search(char * name)
{
    for (int index = 0; index < index_tlist; index++)
    {
        if (strstr(name, tlist->name) != NULL)
        { 
            return index;
        }   
    }

    printf("not found\n");
}

void delete(char * str)
{
    int check = 0;
    tinfo d_array[MAXWORD];
    int index_d_array = 0;
    int count = 0;
    for (int index = 0; index < index_tlist; index++)
    {
        if (strstr(str, tlist->name) != NULL)
        { 
            count++;
            strcpy(d_array[index_d_array++].name, str);
        }

        else if (strstr(str, tlist->phone) != NULL)
        { 
            count++;
            strcpy(d_array[index_d_array++].name, str);
        }

        else if (strstr(str, tlist->memo) != NULL)
        { 
            count++;
            strcpy(d_array[index_d_array++].name, str);
        }
        
    }
    if (count == 0)
    {
        printf("not found\n");
    }

    else //delete selected info 
    {
        for (int i = 0; i < index_d_array; i++)
        {
            printf("%d %s %s %s\n", d_array[i].name, d_array[i].phone, d_array[i].memo);
        }
        printf("which one? : ");
        scanf("%d", &check);

        if (check <= index_d_array)
        {
            int d_index = search(d_array->name);
            for (int i = d_index; i < index_tlist; i++)
            {
                strcpy(tlist[i].name, tlist[i+1].name);
                strcpy(tlist[i].phone, tlist[i+1].phone);
                strcpy(tlist[i].memo, tlist[i+1].memo);
            }
            index_tlist--; 
        }
        else
        {
            printf("range out of delete index \n");
        }
    }
    
}

void list(void)
{

}

int main(int argc, char * argv)
{
    FILE *fp = fopen("data.txt", "r+t");
    char temp[MAXWORD];  
    int check = 0;
    char * temp_fp;

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
    printf("%s\n", argv[0]);

    if (strcmp(argv[0], "-a") == 0) // add option operate
    {
        char check;
        printf("%s %s %s\n", argv[1], argv[2], argv[3]);
        printf("add? [Y/N] : ");
        scanf("%c", &check);
        if (check == 'Y')
        {
            strcpy(tlist[index_tlist].name, argv[1]);
            strcpy(tlist[index_tlist].phone, argv[2]);
            strcpy(tlist[index_tlist].memo, argv[3]);
        }

        else
        {
            return 0;
        }
    }

    else if (strcmp(argv[0], "-d") == 0) // delete option operate
    {
        delete(argv[1]);
    }
    
    else if (strcmp(argv[0] , "-l") == 0) // list option oprate
    {
        list();
    }

    else if (argc > 0) // search type oprate
    {
        printf("%s\n", argv[0]);
        char *keyword;
        int count = 0;
        strcpy(keyword, argv[0]);
        printf("%s\n", keyword);

        // loop for searching
        for (int index = 0; index < index_tlist; index++)
        {
            if (strstr(keyword, tlist->name) != NULL)
            { 
                count++;
                printf("%d %s %s %s \n", count, tlist[index].name, tlist[index].phone, tlist[index].memo);
            }

            else if (strstr(keyword, tlist->phone) != NULL)
            { 
                count++;
                printf("%d %s %s %s \n", count, tlist[index].name, tlist[index].phone, tlist[index].memo);
            }

            else if (strstr(keyword, tlist->memo) != NULL)
            { 
                count++;
                printf("%d %s %s %s \n", count, tlist[index].name, tlist[index].phone, tlist[index].memo);
            }            
        }
        if (count == 0)
        {
            printf("not found \n");
        }
        
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

