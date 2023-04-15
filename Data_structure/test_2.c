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
struct sinfo_node
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





