#include <stdio.h>

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

int n = 0;
int cnt = 0;
sinfo *slist;  // 구조체 타입 포인터 slist 선언.

void to_list(FILE *fp, int Line_num) // 파일로부터 받아들인 정보를 배열에 저장하는 함수를 선언, 매개변수는 파일 포인터를 필요로 한다. 
{
    int i = 0;
    int n = Line_num; // 파일의 줄 수 n으로 넣기. 

    for ( i = 0, i <= n, i++ ) 
    {
        fscanf(fp, "%s %s %c %s %f %d %d", 
        slist.name[i], &slist.gender, slist.city[i], slist.dept[i], &slist.gpa, &slist.height, &slist.weight ) // ?
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



int main(void) // malloc은 메인에서 하기. 
{
    FILE *fp = fopen ( "input.txt", "r+t");
    FILE *Lfp = fopen ( "list.txt", "r+t");
    
    char input[512];
    char tok1[32], tok2[32], tok3[32], tok4[32], tok5[32], tok6[32], tok7[32], tok8[32], tok9[32];

    while(fgets (input, 512, fp ) != NULL)     // fgets 함수로 input 파일에서 fp라는 파일 포인터가 한 문장씩 읽는다. 
    {
        // 공백을 만날 떄마다 끊어서 tok(n)에 저장해줌.
        sscanf(input, "%s%s%s%s%s%s%s%s%s", tok1, tok2, tok3, tok4, tok5, tok6, tok7, tok8, tok9);  
        if (strcmp (tok1, "CREATE") == 0)      // 학생 정보 저장하는 동적 메모리 할당
        {
            slist = malloc(n * sizeof (sinfo)) // (크기 n) x (구조체의 사이즈) 만큼의 공간할당. 그 배열의 첫 자리의 포인터를 slist로 넣어줌.  
        }

        else if ( strcmp (tok1, "LOAD") == 0)  // 리스트 txt에서 학생 정보 입력 받아 이름순으로 저장
        {
            to_list()

        }

        else if (strcmp (tok1, "PRINT") == 0) // 저장한 모든 학생 정보를 출력. 
        {
            process_print ();

        }

        else if (strcmp (tok1, "INSERT") == 0 ) // 학생 정보 입력받아서 이름순에 맞는 위치에 삽입
        {


        }

         else if (strcmp (tok1, "DELETE") == 0 ) // 입력받은 학생의 정보를 삭제할 것
        {
            

        }

        else if (strcmp (tok1, "SEARCH") == 0 ) // 입력받은 학생의 정보를 찾아 출력하기
        {
            process_search ( tok2 );

        }

        else 
        {
            printf("%s is not a keyword. \n", tok1);
        }
    }


}