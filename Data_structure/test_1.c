#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct sinfo
            {
                char name[8];        // 4자
                char* gender;
                char city[8];        // 4자
                char dept[16];       // 8자
                char* gpa;
                char* height;
                char* weight;
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
        process_print();
        // scanf라는 함수는 포인터 변수를 매개변수로 받기 때문에 일반 변수에는 &를 붙여준다. 
    }
} 

int count_list(char Filename[]) // 파일이 총 몇 줄인지 센다. open하지 않아도 실행이 가능한 코드이다. 
{
    FILE *fp = fopen(Filename, "r+t");
    char c; 
    
    while((c = fgetc(fp)) != EOF)
    {
        if ( c == '\n' ) // 개행 문자랑 비교를 하고 싶은거면 작은따옴표로 하기.
        {
            n++;
        }
    }
    rewind(fp); // line count 중 위치가 파일 마지막이 되버린 포인터를 되돌림. 
    fclose(fp);

    return n;
}

void process_print() {
    for (int i = 0; i < n; i++) {
        printf("%s ", slist[i].name);
        printf("%s ", slist[i].gender);
        printf("%s ", slist[i].city);  
        printf("%s ", slist[i].dept);  
        printf("%s ", slist[i].gpa);  
        printf("%s ", slist[i].height);  
        printf("%s\n", slist[i].weight);
    }
}

void sort(sinfo arr[], int size_of_array)  // strcmp로 이름순 정렬 O(n^2) 매개변수로 sinfo 배열과 배열의 크기를 받는다. 
{
    int i, j;
    sinfo temp;

    for(i=0; i<n-1; i++) {
        for(j=i+1; j<n; j++) {
            if(strcmp(slist[i].name, slist[j].name) > 0) 
            {
                temp = slist[i];
                slist[i] = slist[j];
                slist[j] = temp;
            }
        }
    }
    process_print();
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
    FILE *list_fp = fopen ( "list.txt", "r+t");

    char input[512];
    char tok1[32], tok2[32], tok3[32], tok4[32], tok5[32], tok6[32], tok7[32], tok8[32], tok9[32];

    while(fgets (input, 512, fp ) != NULL)     // fgets 함수로 input 파일에서 fp라는 파일 포인터가 한 문장씩 읽는다. 
    {
        // 공백을 만날 떄마다 끊어서 tok(n)에 저장해줌.
        sscanf(input, "%s%s%s%c%s%f%d%d%s", tok1, tok2, tok3, tok4, tok5, tok6, tok7, tok8, tok9);  
        if (strcmp (tok1, "CREATE") == 0)      // 학생 정보 저장하는 동적 메모리 할당
        {
            slist = malloc(n * sizeof (sinfo)); // (크기 n) x (구조체의 사이즈) 만큼의 공간할당. 그 배열의 첫 자리의 포인터를 slist로 넣어줌.  
            printf("CREATE is done=======================\n");
        }
        
        else if ( strcmp (tok1, "LOAD") == 0)  // 리스트 txt에서 학생 정보 입력 받아 이름순으로 저장
        {
            n = count_list(tok2); // list.txt
            printf("%d", n);

            read_list(list_fp, n);
            process_print(); 
            sort(slist, n);
            
            printf("LOAD is done=======================\n");
        }

        else if (strcmp (tok1, "PRINT") == 0) // 저장한 모든 학생 정보를 출력. 
        {
            process_print();
            printf("PRINT is done=======================\n");
        }

        else if (strcmp (tok1, "INSERT") == 0 ) // 학생 정보 입력받아서 이름순에 맞는 위치에 삽입
        {
            // 1. 원하는 인덱스 찾기
            int index = search(slist, n, tok2); 
            int index2 = index;
            

            for(n; n >= index; n --)
            {
                // 2. 인덱스 하나씩 밀기 (뒤에서부터)
                slist[n + 1] = slist[n];
            }
            n = n + 1;

            // 3. 넣기
            memset(slist[index2].name, 0, sizeof(slist[index2].name));
            memset(slist[index2].city, 0, sizeof(slist[index2].name));
            memset(slist[index2].dept, 0, sizeof(slist[index2].name));
        
            
            sscanf(tok2, "%s", slist[index2].name);
            slist[index2].gender = tok3;
            sscanf(tok4, "%s", slist[index2].city);
            sscanf(tok5, "%s", slist[index2].dept);
            slist[index2].gpa = tok6;
            slist[index2].height = tok7;
            slist[index2].weight = tok8;
        
            // 배열 한 칸 늘리고 생긴 마지막 자리(n+1) 에다가 정보 넣기 
            // 정렬 이런 방법으로는 안되나?
            printf("INSERT is done=======================\n");

        }

        else if (strcmp (tok1, "DELETE") == 0 ) // 입력받은 학생의 정보를 삭제할 것
        {
            int DEL_index = 0;

            // 원하는 정보 검색 후 맞는 정보이면 인덱스 반환 시키는 함수
            DEL_index = search(slist, n, tok2);

            // 그 인덱스 삭제. (인덱스 하나씩 땡기기 - 앞에서부터)
            for (DEL_index; DEL_index <= n; DEL_index ++)
            {
                slist[DEL_index] = slist[DEL_index + 1];
            }
            printf("DELETE is done=======================\n");
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
            printf("SEARCH is done=======================\n");
        }

        else 
        {
            printf("%s is not a keyword. \n", tok1);
        }
    }

    fclose(list_fp);
    fclose(fp);


}       