#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct sinfo
            {
                char name[8];        // 4자
                char gender;
                char city[8];        // 4자
                char dept[16];       // 8자
                float gpa;
                int height;
                int weight;
            }sinfo; // 이거 안하면 호출 때마다 struct sinfo라고 해야함? >> yes 

int n = 0;     // 동적 배열의 크기
int cnt = 0;   // 현재 배열 내부에 원소개수
sinfo *slist;  // 구조체 타입 포인터 slist 선언.

void read_list(FILE *fp, int Line_num) // 파일로부터 받아들인 정보를 배열에 저장하는 함수를 선언, 매개변수는 파일 포인터를 필요로 한다. 
{
    int i = 0;
    int n = Line_num; // 파일의 줄 수 n으로 넣기. 

    for ( i = 0; i <= n; i++ ) 
    {
        fscanf(fp, "%s %s %c %s %f %d %d", 
        slist[i].name, &slist[i].gender, slist[i].city, slist[i].dept, &slist[i].gpa, &slist[i].height, &slist[i].weight  ); // ?
        // scanf라는 함수는 포인터 변수를 매개변수로 받기 때문에 일반 변수에는 &를 붙여준다. 
    }
    
} 

int count_list(FILE *fp) // 파일이 총 몇 줄인지 센다. open하지 않아도 실행이 가능한 코드이다. 
{
    int Line_count = 0;
    char c; 

    while(c = fgetc(fp) != EOF)
    {
        if ( c == "\n" )
        {
            Line_count += 1; 
        }

    }
    rewind(fp); // line count 중 위치가 파일 마지막이 되버린 포인터를 되돌림. 

    return Line_count; 
}

void lead_list(FILE *fp) // list 읽어서 출력함. 
{
    int i = 0;

    for ( i = 0; i <= n; i++ ) 
    {
        fprintf(fp, "%s %s %c %s %f %d %d", 
        slist[i].name, &slist[i].gender, slist[i].city, slist[i].dept, &slist[i].gpa, &slist[i].height, &slist[i].weight ); 
        // slist가 전역변수로 정한 것과 매개변수로 정한 것 두개가 있어 혼동을 줄 수 있음. 따라서 slist[i].member 이런식으로 접근해 오류를 방지.
         
    }
}

void sort(sinfo arr[], int n)  // strcmp로 이름순 정렬 O(n^2) 매개변수로 sinfo 배열과 배열의 크기를 받는다. 
{
    int i, j;
    sinfo temp;

    for(i=0; i<n-1; i++) {
        for(j=i+1; j<n; j++) {
            if(strcmp(arr[i].name, arr[j].name) > 0) 
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}


int search(sinfo arr[], int n, char* name)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (strcmp(arr[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}





int main(void) // malloc은 메인에서 하기. 
{
    FILE *fp = fopen ( "input.txt", "r+t");     // 각 파일들 컨트롤 할 포인터들 선언 + 파일 열기. 
    FILE *Lfp = fopen ( "list.txt", "r+t");

    char input[512];
    char tok1[32], tok2[32], tok3[32], tok4[32], tok5[32], tok6[32], tok7[32], tok8[32], tok9[32];

    n = count_list(Lfp); // list.txt 줄 수 세서 변수에 넣음.

    while(fgets (input, 512, fp ) != NULL)     // fgets 함수로 input 파일에서 fp라는 파일 포인터가 한 문장씩 읽는다. 
    {
        // 공백을 만날 떄마다 끊어서 tok(n)에 저장해줌.
        sscanf(input, "%s%s%s%s%s%s%s%s%s", tok1, tok2, tok3, tok4, tok5, tok6, tok7, tok8, tok9);  
        if (strcmp (tok1, "CREATE") == 0)      // 학생 정보 저장하는 동적 메모리 할당
        {
            slist = malloc(n * sizeof (sinfo)); // (크기 n) x (구조체의 사이즈) 만큼의 공간할당. 그 배열의 첫 자리의 포인터를 slist로 넣어줌.  
        }

        else if ( strcmp (tok1, "LOAD") == 0)  // 리스트 txt에서 학생 정보 입력 받아 이름순으로 저장
        {
            to_list(Lfp, n);
            sort(slist, Lfp);
        }

        else if (strcmp (tok1, "PRINT") == 0) // 저장한 모든 학생 정보를 출력. 
        {
            lead_list(Lfp);
        }

        else if (strcmp (tok1, "INSERT") == 0 ) // 학생 정보 입력받아서 이름순에 맞는 위치에 삽입
        {
            // 1. 원하는 인덱스 찾기
            int index = search(slist, n, tok2); 
            int index2 = index;

            for(index; index < n; index ++)
            {
                
                // 2. 인덱스 하나씩 밀기
                slist[index + 1] = slist[index];
                
            }

            // 3. 넣기
            slist[index2] = {tok2,tok3,tok4,tok5,tok6,tok7,tok8};
        
            // 배열 한 칸 늘리고 생긴 마지막 자리(n+1) 에다가 정보 넣기 
            // 정렬 이런 방법으로는 안되나?

        }

        else if (strcmp (tok1, "DELETE") == 0 ) // 입력받은 학생의 정보를 삭제할 것
        {
            sinfo *IN_arr;
            IN_arr = malloc(100 * sizeof(sinfo));
            int DEL_index = 0;

            // 원하는 정보 검색 후 맞는 정보이면 인덱스 반환 시키는 함수
            DEL_index = search(slist, IN_arr);

            // 그 인덱스 삭제. (인덱스 하나씩 땡기기)
            for (DEL_index; DEL_index <= n; DEL_index ++)
            {
                slist[DEL_index] = slist[DEL_index + 1];
            }
        
        }

        else if (strcmp (tok1, "SEARCH") == 0 ) // 입력받은 학생의 정보를 찾아 출력하기
        {
            // 1. 찾기 
            int i = 0;
            int check = 0;

            for (i=0; i<n; i++)
            {
                if (tok2 == slist[i].name)
                {
                    // 2. 그 인덱스의 멤버 출력하기
                    printf("%s %s %c %s %f %d %d", 
                    slist[i].name, &slist[i].gender, slist[i].city, slist[i].dept, &slist[i].gpa, &slist[i].height, &slist[i].weight );
                    check += 1;
                }
            }

            // 없는 경우            
            if (check = 0)
            {
                printf("찾으시는 학생의 정보는 저장되어 있지 않습니다. 정보를 추가해 주세요.");
            }
            
        }

        else 
        {
            printf("%s is not a keyword. \n", tok1);
        }
    }


}       