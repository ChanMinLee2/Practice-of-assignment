#include <stdio.h> 

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

// 먼저 구조체 타입 set 선언 여기에 구조체 정보 다 넣을거임. 
typedef struct sset sset;
struct sset
{
    sinfo svalues[100];
    int count;
};

// 그리고 3,4번 접근할 구조체 타입 map선언. 이걸로는 키 : 값 구조로 사용 
// 아마 키에는 학과 값에는 집합 또는 학과의 학생 수 이렇게 넣을듯?



int main(void) 
{
    FILE *fp = fopen ( "input.txt", "r+t");     // 각 파일들 컨트롤 할 포인터들 선언 + 파일 열기. 

    char input[512];
    char tok1[32], tok2[32], tok3[32], tok4[32], tok5[32], tok6[32], tok7[32], tok8[32], tok9[32];
    while(fgets (input, 512, fp ) != NULL)      
    {
        // 공백을 만날 떄마다 끊어서 tok(n)에 저장해줌.
        sscanf(input, "%s%s%s%s%s%s%s%s%s", tok1, tok2, tok3, tok4, tok5, tok6, tok7, tok8, tok9);  
        
    }
    fclose(fp);
}