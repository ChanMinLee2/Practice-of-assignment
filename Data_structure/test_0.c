#include <stdio.h> 
#include <stdlib.h> 

typedef struct _sinfo    // 구조체 선언과 구조체를 sinfo라는 새로운 변수형으로 사용
{
    char name[8];        // 4자
    char gender;
    char city[8];        // 4자
    char dept[16];       // 8자
    float gpa;
    int height;
    int weight;
} sinfo;

// 동적 배열 : 전체 배열의 수 & 현재 배열에 들어있는 원소의 수 
int n;            // 전체 배열의 수 
int cnt = 0;      // 현재 배열에 있는 원소의 수, 0으로 초기화
sinfo* slist;

// fp로 시작하는 파일의 줄 수 세기
int count_student(FILE* fp)
{
    char str[256];
    int i = 0;
    while (fgets(str, 256, fp) != NULL)
        i++;

    return i;
}

void read_student(FILE* fp)
{
    // 첫번째 줄부터 마지막 줄까지 이동하면서 한줄씩 읽어들여 slist[i]에 저장
    // fscanf()를 사용
    int i;

    for (i = 0; i < n; i++)
    {
        fscanf(fp, "%s %c %s %s %f %d %d", slist[i].name, &slist[i].gender, slist[i].city, slist[i].dept,
            &slist[i].gpa, &slist[i].height, &slist[i].weight);
    }
}

void write_student()
{
    int i;

    for (i = 0; i < n; i++)
        printf("%s %c %s %s %.2f %d %d \n", slist[i].name, slist[i].gender, slist[i].city, slist[i].dept,
            slist[i].gpa, slist[i].height, slist[i].weight);
}

int main()
{
    FILE* fp = fopen("list.txt", "r+t");

    n = count_student(fp);           // n이 count함수를 지나며 포인터가 파일 끝에 위치해있음.
    rewind(fp);                      // 때문에 rewind로 포인터 위치를 파일 처음으로 되돌려줌.

    slist = (sinfo*)calloc(n, sizeof(sinfo));      // calloc()함수를 사용해 동적 배열에 메모리를 할당. (calloc은 메모리 할당을 알아서 해제, malloc은 자동할당해제x )

    read_student(fp);

    write_student(fp);

    fclose(fp);

    system("Pause");

    return 0;

}