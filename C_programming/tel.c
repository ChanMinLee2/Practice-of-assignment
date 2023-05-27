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

tinfo tlist[MAXWORD]; // tel info array
int index_tlist = 0; // count of tlist

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

void delete(char * str) // name, phone
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
            printf("%d %s %s %s\n", i+1, d_array[i].name, d_array[i].phone, d_array[i].memo);
        }
        printf("which one? : ");
        scanf("%d", &check);
        check--; // check is used for index

        // data.txt modify
        FILE *original_file = fopen("data.txt", "r");  // open the original file in read mode
        FILE *new_file = fopen("data.txt", "w");  // open a new file in write mode

        if (original_file == NULL || new_file == NULL) 
        {
            printf("Unable to open the file(s).\n");
            return;
        }      

        char line[100]; // buffer

        // read the original file line by line
        while (fgets(line, sizeof(line), original_file) != NULL) 
        {
            // Check if the line should be deleted
            if(strstr(line, d_array[check].name) != NULL )  
            {
                ; // no writing to new file
            }
            else
            {
                // Write the line to the new file if it should not be deleted
                fputs(line, new_file);
            }
            fclose(original_file);  // Close the original file
            fclose(new_file);  // Close the new file

            // Delete the original file
            if (remove("data.txt") != 0) {
                printf("Unable to delete the original file.\n");
                return;
            }

            // Rename the new file to have the same name as the original file
            if (rename("temp.txt", "data.txt") != 0) {
                printf("Unable to rename the new file.\n");
                return;
            }
        }
    }
}

void list(void)
{
    for (int list_index = 0; list_index < index_tlist; list_index++)
    {
        printf("%d %s %s %s \n", list_index+1, tlist[list_index].name, tlist[list_index].phone, tlist[list_index].memo); 
    }
}


int main(int argc, char * argv[])
{
    FILE *fp = fopen("data.txt", "r+t");
    char temp[MAXWORD];  
    int check = 0;
    char * temp_fp;

    while(fscanf(fp,"%s",temp) != EOF)
    {
        char * temp_fp = temp;
        strtok(temp,":");
        int push_point = 0;
        while (temp_fp != NULL)
        {
            //printf("%s\n", temp_fp);
            if (check == 0)
            {
                for (int scan = 0; scan < index_tlist; scan++)
                {
                    if(strcmp(tlist[scan].name, temp_fp) >= 0)
                    {
                        push_point = scan;
                    }

                    if (push_point > 0)
                    {
                        tlist[scan+1] = tlist[scan];
                    }
                    
                }
                strcpy(tlist[push_point].name, temp_fp);
                check++;
            }
            
            else if (check == 1)
            { 
                strcpy(tlist[push_point].phone, temp_fp);
                check++;
            }
            
            else if (check == 2)
            {
                strcpy(tlist[push_point].memo, temp_fp);
                index_tlist++;
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
        int push_point = 0;
        printf("%s %s %s\n", argv[1], argv[2], argv[3]);
        printf("add? [Y/N] : ");
        scanf("%c", &check);
        if (check == 'Y' || check == 'y')
        {
            for (int scan = 0; scan < index_tlist; scan++)
            {
                if( strcmp(tlist[scan].name, argv[1]) >= 0 )
                {
                    push_point = scan;
                }

                if (push_point > 0 )
                {
                    tlist[scan + 1] = tlist[scan];
                }
            }
            
            strcpy(tlist[push_point].name, argv[1]);
            strcpy(tlist[push_point].phone, argv[2]);
            strcpy(tlist[push_point].memo, argv[3]);

            FILE *fp = fopen("data.txt", "r + t");
            fprintf(fp," %s:%s:%s", argv[1], argv[2], argv[3]);
            fclose(fp);
        }

        else
        {
            return 0;
        }
    }

    else if (strcmp(argv[0], "-d") == 0) // delete option operate
    {
        delete(argv[1], argv[2]);
    }
    
    else if (strcmp(argv[0] , "-l") == 0) // list option oprate
    {
        list();
    }

    else if (argc > 0) // search type oprate
    {
        printf("search start - argv %s\n", argv[0]);
        char *keyword;
        int count = 0;
        strcpy(keyword, argv[0]); // 
        printf("search keyword %s\n", keyword);

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

