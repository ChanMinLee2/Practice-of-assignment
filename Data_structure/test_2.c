#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sinfo sinfo;  // 학생정보를 저장하는 구조체
struct sinfo
{
    char name[10];        // 4자
    char gender[8];
    char city[10];        // 4자
    char dept[20];       // 8자
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
sinfo_node* create_node(sinfo info)
{
    sinfo_node *node = (sinfo_node*)malloc(sizeof(sinfo_node));
    node->student_info = info;  // 노드 내부 멤버인 student_info에 info 저장 
    node->next = NULL;          // 노드 내부 멤버인 next에 NULL을 저장 ( 첫 일반 노드 )

    return node;
}

// 단일 연결 리스트에서 새로운 정보를 새로운 노드에 담아 올바른 위치에 연결해주는 함수 >> 이걸로 load하기. 
void append(sinfo_node **head, sinfo info) // headnode, 구조체 변수 
{
    sinfo_node* node = *head; // head node는 create함수에서 이미 정의됨 , 왜 *head??
    
    if (*head == NULL)        // head node가 NULL = 비었다는 뜻 
    {
        *head = node;         // 새로 생성된 node의 주소를 *head에 저장
    } 
    else // 연결 리스트가 비어있지 않음
    {
        sinfo_node* curr = *head;   // 시작점(head)부터 curr로 접근
        while(curr -> next != NULL) // 순차반복 (null이면 멈춤)
        {
            // 1.적절한 위치 찾기
            if(curr->next->student_info.name[0] > info.name[0])
                break;
            curr = curr -> next; // ??
        }
        //2. 새로운 노드 생성
        sinfo_node* new_node;
        new_node -> student_info = info; 

        //3. 링크 갱신
        new_node->next = curr -> next;
        curr -> next = new_node;

        // curr -> next = node; // next == NULL이면 새로운 노드를 넣어줌 ?? 이거 안해도 될듯
    }
}

void print_node(sinfo_node* node) // 연결 리스트에서 입력받은 한 노드의 구조체 정보를 출력하는 함수
{
    
    printf("%s ", node -> student_info.name);
    printf("%s ", node -> student_info.gender);
    printf("%s ", node -> student_info.city);  
    printf("%s ", node -> student_info.dept);  
    printf("%s ", node -> student_info.gpa);  
    printf("%s ", node -> student_info.height);  
    printf("%s\n", node -> student_info.weight);
}

void search(sinfo_node **head, sinfo info)  // 원하는 정보가 연결리스트에 있는지 검색하는 함수
{
    sinfo_node* curr = *head;
    
    while(curr -> next != NULL) // 순차반복 (null이면 멈춤)
        {
            if(curr -> student_info.name == info.name) // 연결리스트의 한 노드가 입력받은 정보와 같으면 그 노드의 구조체 배열 출력
            {   
                print_node(curr);
            }
            curr = curr -> next; 
        }
}

void delete(sinfo_node **head, sinfo info)
{
    sinfo_node* curr = *head;
    sinfo_node* del_node;

    while(curr -> next != NULL) // 순차반복 (null이면 멈춤)
    {
        // 1.적절한 위치 찾기
        if(curr->next->student_info.name[0] > info.name[0])
            break;
        curr -> next = del_node -> next; // ??
    }
    // 2.링크 갱신
    del_node = curr -> next;
    curr -> next = del_node -> next;

    // 3.할당 해제
    free(del_node);
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
            printf("CREATE is done=======================\n");
        }
        
        else if ( strcmp (tok1, "LOAD") == 0)  // 리스트 txt에서 학생 정보 입력 받아 이름순으로 연결리스트에 저장
        {
            printf("LOAD is done=======================\n");
        }

        else if (strcmp (tok1, "PRINT") == 0) // 저장한 모든 학생 정보를 출력. 
        {
            printf("PRINT is done=======================\n");
        }

        else if (strcmp (tok1, "INSERT") == 0 ) // 학생 정보 입력받아서 이름순에 맞는 위치에 삽입
        {
            printf("INSERT is done=======================\n");

        }

        else if (strcmp (tok1, "DELETE") == 0 ) // 입력받은 학생의 정보를 삭제할 것
        {
            printf("DELETE is done=======================\n");
        }

        else if (strcmp (tok1, "SEARCH") == 0 ) // 입력받은 학생의 정보를 찾아 출력하기
        {
            printf("SEARCH is done=======================\n");
        }

        else 
        {
            printf("%s is not a keyword. \n", tok1);
        }
    }
    fclose(fp);


}





