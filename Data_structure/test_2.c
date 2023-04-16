#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sinfo sinfo;  // 학생정보를 저장하는 구조체
struct sinfo
{
    char name[10];        // 4자
    char gender[8];
    char city[10];        // 4자
    char dept[20];        // 8자
    char gpa[10];
    char height[10];
    char weight[10];
};

typedef struct _node sinfo_node; // 학생정보를 저장하는 연결리스트의 노드 구조체
struct _node
{
    sinfo student_info; // 학생정보 구조체 변수선언 (item)
    sinfo_node* next; // 각 노드에 접근해 작업을 수행할 노드형 포인터 변수 선언(link)
};


// 단일 연결 리스트의 노드를 동적으로 생성하는 함수 create_node
void create_node()
{
    sinfo_node *head_node; // head node를 create함수에서 정의 --- 왜 할당해야함?
    head_node = (sinfo_node*)malloc(sizeof(sinfo_node)); // 메모리 할당
    head_node -> next = NULL; // 링크 NULL로 초기화
}

sinfo_node * head_node; // 전역

// 단일 연결 리스트에서 새로운 정보를 새로운 노드에 담아 올바른 위치에 연결해주는 함수 >> 이걸로 load하기. 
void append_node(sinfo info) // headnode, 구조체 변수 
{  
    sinfo_node * temp_node = (sinfo_node*)malloc(sizeof(sinfo_node)); // 0. 첫 노드를 만듦
    strcpy(temp_node->student_info.name, info.name);
    strcpy(temp_node->student_info.gender, info.gender);
    strcpy(temp_node->student_info.city, info.city);
    strcpy(temp_node->student_info.dept, info.dept);
    strcpy(temp_node->student_info.gpa, info.gpa);
    strcpy(temp_node->student_info.height, info.height);
    strcpy(temp_node->student_info.weight, info.weight);

    head_node -> next = temp_node;  // head node의 링크를 첫 노드로 연결
    temp_node -> next = NULL;
    sinfo_node * current_node = head_node; // 이 함수에서 사용할 탐색용 노드 포인터 생성 

    while(current_node->next->student_info.name > info.name) // 1. 위치 찾기
    {
        temp_node -> next = current_node -> next; // 2. 링크 갱신
        current_node -> next = temp_node;         // 2. ..
    }
}

void load_list(void) // 파일로부터 받아들인 정보를 연결리스트에 저장하는 함수를 선언 (1회용) 
{
    // 리스트열고
    FILE *list_fp = fopen("list.txt", "r+t");

    // 입력받기 (temp)
    sinfo_node * curr_node = head_node;
    char temp_array[100];
    while( fgets(temp_array,100,list_fp) != NULL )
    {
        sinfo_node * temp_node = (sinfo_node*)malloc(sizeof(sinfo_node));
        
        sscanf("%s%s%s%s%s%s%s", temp_node->student_info.name, temp_node->student_info.gender, temp_node->student_info.city,
        temp_node->student_info.dept, temp_node->student_info.gpa, temp_node->student_info.height, temp_node->student_info.weight);

        // head node(curr_node) 뒤에다 붙이고 temp 링크갱신 NULL
        curr_node -> next = temp_node;
        temp_node -> next = NULL;
    }
}

void print_node() // 연결 리스트에서 입력받은 한 노드의 구조체 정보를 출력하는 함수
{
    sinfo_node * curr_node = head_node;
    while(curr_node -> next != NULL)
    {
        printf("%s ", curr_node -> student_info.name);
        printf("%s ", curr_node -> student_info.gender);
        printf("%s ", curr_node -> student_info.city);  
        printf("%s ", curr_node -> student_info.dept);  
        printf("%s ", curr_node -> student_info.gpa);  
        printf("%s ", curr_node -> student_info.height);  
        printf("%s\n", curr_node -> student_info.weight);
    }
}

void swap(char string1[], char string2[])
{
    char temp_string[100]; 
    strcpy(temp_string, string2);
    strcpy(string2, string1);
    strcpy(string1, temp_string);
}

void sort_list(void)
{
    sinfo_node * curr_node = head_node;             // for문에서 i 
    sinfo_node * curr2_node = curr_node -> next;    // for문에서 j

    while(curr_node->next != NULL)
    {
        while(curr2_node->next != NULL)
        {
            if(curr_node->student_info.name > curr2_node->student_info.name)
            {
                swap(curr_node->student_info.name,curr2_node->student_info.name);
                swap(curr_node->student_info.gender,curr2_node->student_info.gender);
                swap(curr_node->student_info.city,curr2_node->student_info.city);
                swap(curr_node->student_info.dept,curr2_node->student_info.dept);
                swap(curr_node->student_info.gpa,curr2_node->student_info.gpa);
                swap(curr_node->student_info.height,curr2_node->student_info.height);
                swap(curr_node->student_info.weight,curr2_node->student_info.weight);
            }
            curr2_node = curr2_node -> next; // for문에서 증가연산자
        }
        curr_node = curr_node -> next; 
    }
}

void search_node(char name[])  // 원하는 정보가 연결리스트에 있는지 검색하는 함수
{
    sinfo_node * curr_node = head_node;

    while(curr_node->next != NULL)
    {
        if (strcmp(curr_node->student_info.name, name) == 0) // 있음
        {
            printf("%s ", curr_node -> student_info.name);
            printf("%s ", curr_node -> student_info.gender);
            printf("%s ", curr_node -> student_info.city);  
            printf("%s ", curr_node -> student_info.dept);  
            printf("%s ", curr_node -> student_info.gpa);  
            printf("%s ", curr_node -> student_info.height);  
            printf("%s\n", curr_node -> student_info.weight);
        }
        printf("찾으시는 정보는 리스트에 없습니다. \n");
    }
}

void delete_node(char del_name[])
{
    sinfo_node * curr_node = head_node;
    sinfo_node * del_node;

    while(curr_node->next != NULL)
    {
        if (strcmp(curr_node->next->student_info.name,del_name) == 0)
        {       
            del_node = curr_node -> next;
            curr_node -> next = del_node ->next;
        }
        
        printf("삭제를 요청한 정보는 리스트에 없습니다. \n");
    }
}

int main(void) 
{
    FILE *fp = fopen ( "input.txt", "r+t");     // 각 파일들 컨트롤 할 포인터들 선언 + 파일 열기. 

    char input[512];
    char tok1[32], tok2[32], tok3[32], tok4[32], tok5[32], tok6[32], tok7[32], tok8[32], tok9[32];
    while(fgets (input, 512, fp ) != NULL)      
    {
        // 공백을 만날 떄마다 끊어서 tok(n)에 저장해줌.
        sscanf(input, "%s%s%s%s%s%s%s%s%s", tok1, tok2, tok3, tok4, tok5, tok6, tok7, tok8, tok9);  
        if (strcmp (tok1, "CREATE") == 0)      
        {
            
            create_node(); // first 노드 정의
            printf("CREATE is done=======================\n");
        }
        
        else if ( strcmp (tok1, "LOAD") == 0)  // 리스트 txt에서 학생 정보 입력 받아 이름순으로 연결리스트에 저장(반복해야함)
        {
            load_list();
            printf("LOAD is done=======================\n");
        }

        else if (strcmp (tok1, "PRINT") == 0) // 저장한 모든 학생 정보를 출력. 
        {
            print_node();
            printf("PRINT is done=======================\n");
        }

        else if (strcmp (tok1, "INSERT") == 0 ) // 학생 정보 입력받아서 이름순에 맞는 위치에 삽입
        {
            sinfo insert_info;
            strcpy(insert_info.name, tok2);
            strcpy(insert_info.name, tok3);
            strcpy(insert_info.name, tok4);
            strcpy(insert_info.name, tok5);
            strcpy(insert_info.name, tok6);
            strcpy(insert_info.name, tok7);
            strcpy(insert_info.name, tok8);

            append_node(insert_info);
            printf("INSERT is done=======================\n");

        }

        else if (strcmp (tok1, "DELETE") == 0 ) // 입력받은 학생의 정보를 삭제할 것
        {
            delete_node(tok2);
            printf("DELETE is done=======================\n");
        }

        else if (strcmp (tok1, "SEARCH") == 0 ) // 입력받은 학생의 정보를 찾아 출력하기
        {
            search_node(tok2);
            printf("SEARCH is done=======================\n");
        }

        else 
        {
            printf("%s is not a keyword. \n", tok1);
        }
    }
    fclose(fp);


}





