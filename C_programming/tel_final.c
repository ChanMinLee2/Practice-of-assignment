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

// sort function by alphabetical order
void sorting(void)
{
	tinfo temp; // temp valiable to swap
	// bubble sort
	for(int i = 0; i < index_tlist; i++)
	{
		int index_min = i;
		for(int index = i; index < index_tlist; index++)
		{
			if (index_min != index && strcmp(tlist[index_min].name, tlist[index].name) > 0)
			{
				index_min = index;
			}
		}
		//swap
		temp = tlist[index_min];
		tlist[index_min] = tlist[i];
		tlist[i] = temp;
	}

	// data file open, and rewrite by tlist
	FILE *fp = fopen("data.txt", "w+");
	for(int n = 0; n < index_tlist; n++)
	{
		fprintf(fp, "%s:%s:%s\n", tlist[n].name, tlist[n].phone, tlist[n].memo);
	}
	fclose(fp); // file close
}

// search function ketword in data.txt(tlist) 
int search(char * keyword)
{	
	// valiables to use buffer
        int search_buffer[MAXWORD];
        int buffer_index = 0;
	// storing elements that satisfy the condition of searching to buffer
        for (int index = 0; index < index_tlist; index++)
        {
                if (strstr(tlist[index].name, keyword) != NULL)
                { 
                        search_buffer[buffer_index++] = index;
                }   

                else if (strstr(tlist[index].phone, keyword) != NULL)
                {
                        search_buffer[buffer_index++] = index;
                }

                else if (tlist[index].memo != NULL && strstr(tlist[index].memo, keyword) != NULL)
                {
                        search_buffer[buffer_index++] = index;
                }
        }

	int temp = 0;
	// search result - each elements printing
        for (int i = 0; i < buffer_index; i++)
        {
		temp = search_buffer[i];
        	printf("%d %s %s %s\n", i+1, tlist[temp].name, tlist[temp].phone, tlist[temp].memo);
        }
        
	// result print
        if (buffer_index == 0)
        {
                printf("not found\n");
        }
        else
        {
                printf("match found\n");
        }
}

// add funtion to add new info in data.txt
void add(char * str1, char * str2, char* str3 ) // numeric order in alphabet
{
        // valiables declation
        char check;
        int point_check = 0;
        int push_point = 0;
        // check for user
        printf("%s %s %s\n", str1, str2, str3);
        printf("add? [Y/N] : ");
        scanf("%c", &check);
        // if check is y or Y, add new info to tlist and data.txt 
        if (check == 'Y' || check == 'y')
        {
                // loop for location to add new info 
                for (int scan = 0; scan < index_tlist; scan++) 
                {
                    //printf("index_tlist : %d, scan : %d\n", index_tlist, scan);
                    //printf("tlist[scan] : %s str1 : %s\n", tlist[scan].name , str1);
                    if(strcmp(tlist[scan].name, str1) >= 0) // equal name - (diffrent person) including 
                    {
                        push_point = scan;
                        point_check++;
                        //printf("push_point : %d, scan : %d\n", push_point, scan);
                        break;
                    }
                }

                int flag = 0;
                if (point_check == 0) // no if sentence True
                {
                        flag = index_tlist;
                }
                else
                {
                        flag = push_point;
                }
                
                //printf("flag : %d\n", flag);
                if (flag != index_tlist)
                {
                        for (int push_index = index_tlist; push_index >= push_point; push_index--) 
                        {
                                tlist[push_index+1] = tlist[push_index];
                        }
                }
                // add new info to tlist
                strcpy(tlist[flag].name, str1);
                strcpy(tlist[flag].phone, str2);
                strcpy(tlist[flag].memo, str3);

                index_tlist++; // by add info 
                
                //for (int i = 0; i < index_tlist; i++)
                //{
                //        printf("%s\n",tlist[i].name);
                //}   

                // tlist is complete, data.txt modifying starts
                FILE *fp = fopen("data.txt", "w+");
                for (int index_add = 0; index_add < index_tlist; index_add++)
                {
                        //printf("%s:%s:%s\n", tlist[index_add].name, tlist[index_add].phone, tlist[index_add].memo);
                        fprintf(fp,"%s:%s:%s\n", tlist[index_add].name, tlist[index_add].phone, tlist[index_add].memo);
		}
		
		printf("good add\n");
        	fclose(fp);
        }

        else // not Y or y, it is not invalid
        {
                printf("add not be oprated\n");
                return;
        }
}

// funtion to delete the info that user selected in data.txt
void delete(char * keyword) 
{
	// valiables declation
        int check = 0;
        int d_array[MAXWORD];
        int index_d_array = 0;
        int count = 0;
	// delete keyword scan, result index can be stored in d_array
        for (int index = 0; index < index_tlist; index++)
        {
                if (strstr(tlist[index].name, keyword) != NULL)
                { 
                        count++;
                        d_array[index_d_array++] = index;
                }

                else if (strstr(tlist[index].phone, keyword) != NULL)
                { 
                        count++;
                        d_array[index_d_array++] = index;
                }

                else if (strstr(tlist[index].memo, keyword) != NULL)
                { 
                        count++;
                        d_array[index_d_array++] = index;
                }
        }
        //printf("index_darray : %d\n", index_d_array);

        // input info is not in tlist
        if (index_d_array == 0) 
        {
                printf("not found\n");
        }

        else //input info is in tlist, delete selected info 
        {
                //printf("start delete process, index darray : %d \n", index_d_array);
                int index_del = 0;
                // check for user
                for (int i = 0; i < index_d_array; i++)
                {
                        index_del = d_array[i];
                        printf("%d %s %s %s\n", i+1, tlist[index_del].name, tlist[index_del].phone, tlist[index_del].memo);
                }
                printf("which one? : ");
                scanf("%d", &check);
                check--; // check is used for index

                if (check >= 0 && check < index_d_array)
                {
                        // tlist modifying
                        index_del = d_array[check]; 
                        for (index_del; index_del < index_tlist; index_del++)
                        {
                                tlist[index_del] = tlist[index_del+1];
                        }
                        index_tlist--; // one person's info delete in array, not data file
                        //printf("%d\n", index_tlist);

                        // tlist is complete, data.txt modifying starts
                        FILE *fp = fopen("data.txt", "w+");
                        for (int index = 0; index < index_tlist; index++)
                        {
                                //printf("%s:%s:%s\n", tlist[index].name, tlist[index].phone, tlist[index].memo);
                                fprintf(fp,"%s:%s:%s\n", tlist[index].name, tlist[index].phone, tlist[index].memo);
                        }
                        printf("good delete\n");

                        fclose(fp);
                        return;
                }
                else // check's range over 
                {
                        printf("delete not be operated\n");
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

int main(int argc, char * argv[]) //commandline arguments
{
        // data file open
        FILE *fp = fopen("data.txt", "r+t");
        // buffer and buffer pointer for input from data.txt
        char temp[MAXWORD];  
        char * temp_fp;

        // loop for input tel info from data.txt to tlist
        while(fscanf(fp,"%s",temp) != EOF) 
        {
                int check = 0;
                char * temp_fp = temp;
                //input line tokenization by strtok
                strtok(temp,":");
                // loop for inputing info from line to tlist, each token to right space by if sentences
                while (temp_fp != NULL)
                {
                        //printf("%s\n", temp_fp);
                        if (check == 0)
                        {
                                strcpy(tlist[index_tlist].name, temp_fp);
                                check++;
                        }
                        
                        else if (check == 1)
                        {
                                // no memo case covering - index++
                                strcpy(tlist[index_tlist++].phone, temp_fp);
                                check++;
                        }
                        
                        else if (check == 2)
                        {
                                strcpy(tlist[index_tlist-1].memo, temp_fp);
                                check++;
                        }
                        temp_fp = strtok(NULL, ":"); // doing like loop's increment operator - retokenization from broken pointer position 
                }
        
        }
        temp_fp = strtok(temp, ":"); // last tok
       
       	sorting();
        // for debug
        //for (int i = 0; i < index_tlist; i++)
        //{
        //    printf("%s %s %s\n", tlist[i].name, tlist[i].phone, tlist[i].memo);   
        //}

        // commandline arguments control - no filename storing
        argv++;
        argc--;
        //printf("%s %d %d\n", argv[0], argc, index_tlist);

        if (argv[0] != NULL && strcmp(argv[0], "-a") == 0) // add option operate
        {
        	// exception process
        	if(argv[1] != NULL && argv[2] != NULL) // argv[3] is memo, it is not essential
        		add(argv[1], argv[2], argv[3]);
        	else
        		printf("not invalid keyword input\n");
        }

        else if (argv[0] != NULL && strcmp(argv[0], "-d") == 0) // delete option operate
        {
        	// exception process
        	if(argv[1] != NULL)
                	delete(argv[1]);
        	else
        		printf("no keyword\n");
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
        	printf(" 0. what is this?\n");
        	printf(" : tel info(name, phone, memo) list program in order of alphabet\n");
         	printf(" : in alphabet order, upper case is front than lower case\n\n");
        	printf(" 1. how to input\n");
         	printf(" : ./tel [-adl] words \n");
    	 	printf(" : ex1) ./tel -a Lee 01088776655 plz \n");
        	printf(" : ex2) ./tel -d Le \n\n");
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
                printf(" : it can add one person's new info to list of tel by alphabetic order \n\n");
                printf(" 2-3. delete option\n");
                printf(" : ex) ./tel -d word \n");
                printf(" : it can delete selected one person's info in list of tel \n\n");
                printf(" 2-4. list option\n");
                printf(" : ex) ./tel - l words \n");
                printf(" : it can print every elements in list of tel \n\n");
        }
        return 0;
}

