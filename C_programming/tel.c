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

tinfo tlist[MAXWORD]; // tel info arrays
int index_tlist = 0; // count of tlist

int search(char * keyword)
{
    int search_buffer[MAXWORD];
    int buffer_index = 0;
    for (int index = 0; index < index_tlist; index++)
    {
        if (strstr(keyword, tlist[index].name) != NULL)
        { 
            search_buffer[buffer_index++] = index;
            continue;
        }   

        else if (strstr(keyword, tlist[index].phone) != NULL)
        {
            search_buffer[buffer_index++] = index;
            continue;
        }

        else if (tlist[index].memo != NULL && strstr(keyword, tlist[index].memo) != NULL)
        {
            search_buffer[buffer_index++] = index;
            continue;
        }
    }
    for (int i = 0; i < buffer_index; i++)
    {
        printf("%d %s %s %s\n", i+1, tlist[i].name, tlist[i].phone, tlist[i].memo);
    }
    
    if (buffer_index == 0)
    {
        printf("not found\n");
    }
    else
    {
        printf("match found\n");
    }
}

void add(char * str1, char * str2, char* str3 ) // numeric order in alphabet
// 이거 하나 추가하면 왜 list 옵션에서 5개 되어야 하는데 4개 밖에없지? bae 날아감...
{
    char check;
    int push_point = 0;
    printf("%s %s %s\n", str1, str2, str3);
    printf("add? [Y/N] : ");
    scanf("%c", &check);
    if (check == 'Y' || check == 'y')
    {
        for (int scan = 0; scan < index_tlist; scan++)
        {
            if (scan == index_tlist-1 && strcmp(tlist[scan].name, str1) <= 0 )
            {
                push_point = index_tlist;
                break;
            }
            printf("index_tlist : %d, scan : %d\n", index_tlist, scan);
            printf("%s %s\n", tlist[scan].name , str1);
            if( strcmp(tlist[scan].name, str1) >= 0 )
            {
                push_point = scan;
                printf("push_point : %d, scan : %d\n", push_point, scan);
            }

            if (push_point > 0 )
            {
                tlist[scan + 1] = tlist[scan];
            }
        }

        index_tlist++;
        strcpy(tlist[push_point].name, str1);
        strcpy(tlist[push_point].phone, str2);
        strcpy(tlist[push_point].memo, str3);
        
        for (int i = 0; i < index_tlist; i++)
        {
            printf("%s\n",tlist[i].name);
        }   

        FILE *fp = fopen("data.txt", "w");
        for (int index_add = 0; index_add < index_tlist; index_add++)
        {
            printf("%s:%s:%s\n", tlist[index_add].name, tlist[index_add].phone, tlist[index_add].memo);
            fprintf(fp,"%s:%s:%s\n", tlist[index_add].name, tlist[index_add].phone, tlist[index_add].memo);
        }
        
        fclose(fp);
    }

    else
    {
        return;
    }
}

void delete(char * keyword) // 왜못받는데 미친놈아
{
    int check = 0;
    tinfo d_array[MAXWORD];
    int index_d_array = 0;
    int count = 0;
    for (int index = 0; index < index_tlist; index++)
    {
        if (strstr(keyword, tlist[index].name) != NULL)
        { 
            count++;
            strcpy(d_array[index_d_array].name, keyword);
            printf("strcopy success : %s\n", d_array[index_d_array].name);
        }

        else if (strstr(keyword, tlist[index].phone) != NULL)
        { 
            count++;
            strcpy(d_array[index_d_array++].phone, keyword);
            printf("strcopy success : %s\n", d_array[index_d_array].phone);
        }

        else if (strstr(keyword, tlist[index].memo) != NULL)
        { 
            count++;
            strcpy(d_array[index_d_array-1].memo, keyword);
            printf("strcopy success : %s\n", d_array[index_d_array].memo);
        }
        
    }
    printf("count : %d\n", count);
    if (count == 0)
    {
        printf("not found\n");
    }

    else //delete selected info 
    {
        printf("start delete process, index darray : %d \n", index_d_array);
        for (int i = 0; i < index_d_array; i++)
        {
            printf("%d %s %s %s\n", i+1, d_array[i].name, d_array[i].phone, d_array[i].memo);
        }
        printf("which one? : ");
        scanf("%d", &check);
        check--; // check is used for index

        char line[100]; // buffer

        if (check >= 0 && check < index_tlist)
        {
            // data.txt modify
            FILE *original_file = fopen("data.txt", "r");  // open the original file in read mode
            FILE *new_file = fopen("data.txt", "w");       // open a new file in write mode

            if (original_file == NULL || new_file == NULL) 
            {
                printf("Unable to open the file(s).\n");
                return;
            }

            // read the original file line by line
            while (fgets(line, sizeof(line), original_file) != NULL) 
            {
                printf("line : %s\n", line);
                // Check if the line should be deleted
                if(strstr(line, d_array[check].name) != NULL )  
                {
                    ; // no writing to new file
                }
                else
                {
                    // write the line to the new file if it should not be deleted
                    fputs(line, new_file);
                    printf("selected line : %s\n", line);
                }
                fclose(original_file);  // close the original file
                fclose(new_file);  // close the new file

                // delete the original file
                if (remove("data.txt") != 0) 
                {
                    printf("Unable to delete the original file.\n");
                    return;
                }

                // rename the new file to have the same name as the original file
                if (rename("temp.txt", "data.txt") != 0) 
                {
                    printf("Unable to rename the new file.\n");
                    return;
                }
            }
        }

        else // not valid input by user 
        {
            printf("invalid access");
            return;
        }
    }
}

// tel list printing funtion 
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
    
    char * temp_fp;

    while(fscanf(fp,"%s",temp) != EOF) 
    {
        int check = 0;
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
                strcpy(tlist[index_tlist++].phone, temp_fp);
                check++;
            }
            
            else if (check == 2)
            {
                strcpy(tlist[index_tlist-1].memo, temp_fp);
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
    
    for (int i = 0; i < index_tlist; i++)
    {
        printf("%s %s %s\n", tlist[i].name, tlist[i].phone, tlist[i].memo);   
    }

    argv++;
    argc--;
    printf("%s %d %d\n", argv[0], argc, index_tlist);

    if (argv[0] != NULL && strcmp(argv[0], "-a") == 0) // add option operate
    {
        add(argv[1], argv[2], argv[3]);
    }

    else if (argv[0] != NULL && strcmp(argv[0], "-d") == 0) // delete option operate
    {
        delete(argv[1]);
    }
    
    else if (argv[0] != NULL && strcmp(argv[0] , "-l") == 0) // list option oprate
    {
        list();
    }

    else if (argc > 0) // search type oprate
    {
        search(argv[0]);
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

