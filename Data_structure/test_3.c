#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM 100

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

typedef struct smap smap;
struct smap
{
    char keys[MAX_NUM][MAX_NUM]; // Q3에서는 dept Q4에서는 city
    int values[MAX_NUM]; // Q3에서는 dept마다의 학생 수
    int count;
};

typedef struct smap_Q5 smap_Q5;
struct smap_Q5
{
    char keys[MAX_NUM][MAX_NUM]; // Q3에서는 dept Q4에서는 city
    sinfo svalues[MAX_NUM]; // Q3에서는 dept마다의 학생 수
    int count;
};

// 그리고 3,4번 접근할 구조체 타입 map선언. 이걸로는 키 : 값 구조로 사용 

// 아마 키에는 학과 값에는 집합 또는 학과의 학생 수 이렇게 넣을듯?

void Q1(sset sset)
{
    sinfo moon;
    for(int i = 0; i < sset.count; i++)
    {
        if(strcmp(sset.svalues[i].name, "김문희") == 0)
        {
            moon = sset.svalues[i];
        }
    }

    for(int i = 0; i < sset.count; i++)
    {
        if(strcmp(sset.svalues[i].name, moon.name) == 0)
        {
            printf("김문희가 사는 곳은 %s입니다. \n", sset.svalues[i].city);
        }
    }
}

void Q2(sset sset)
{
    sinfo chun;
    for(int i = 0; i < sset.count; i++)
    {
        if(strcmp(sset.svalues[i].name, "천하은") == 0)
        {
            chun = sset.svalues[i];
        }
    }

    int count_Q2 = 0;
    for(int i = 0; i < sset.count; i++)
    {
        if((atoi(sset.svalues[i].gpa)) > (atoi(chun.gpa)))
        {
            count_Q2++;
        }
    }
    printf("천하은보다 성적이 높은사람 수 : %d \n", count_Q2);
}

void Q3(sset sset, smap smap)
{
    int max = 0;
    for(int i = 0; i < sset.count; i++)
    {
        for(int j = 0; j < smap.count; j++)
        {
            if(smap.count == 8)
            {
                if(strcmp(smap.keys[j], sset.svalues[i].dept) == 0)
                {
                    smap.values[j]++;
                    continue;
                }
            }

            else 
            {
                if(strcmp(smap.keys[j], sset.svalues[i].dept) == 0)
                {
                    smap.values[j]++;
                    continue;
                }
                else
                {
                    strcpy(smap.keys[smap.count], sset.svalues[i].dept);
                    (smap.values[(smap.count)++])++;
                }
            }
        }
    }

    for (int i = 0; i < smap.count; i++)
    {
        if (smap.values[i] < smap.values[i+1])
        {
            max = smap.values[i+1];
        }
    }

    printf("%d \n", max);
}

void Q4(sset sset, smap smap)
{
    int max = 0;
    for(int i = 0; i < sset.count; i++)
    {
        for(int j = 0; j < smap.count; j++)
        {
            if(smap.count == 8)
            {
                if(strcmp(smap.keys[j], sset.svalues[i].city) == 0)
                {
                    smap.values[j]++;
                    continue;
                }
            }

            else 
            {
                if(strcmp(smap.keys[j], sset.svalues[i].city) == 0)
                {
                    smap.values[j]++;
                    continue;
                }
                else
                {
                    strcpy(smap.keys[smap.count], sset.svalues[i].city);
                    (smap.values[(smap.count)++])++;
                }
            }
        }
    }

    // 지역 크기 순으로 출력하기. 
    // 코드
}
void Q5(sset sset, smap_Q5 smap_Q5, char* name)
{
    int search_index = 0;
    int check_same = 0;
    for(int i = 0; i < sset.count; i++)
    {
        smap_Q5.svalues[i] = sset.svalues[i];
        smap_Q5.count++;
        strcpy(smap_Q5.keys[i], sset.svalues[i].name);
    }

    for (int j = 0; j < smap_Q5.count; j++)
    {
        if(strcmp(name, smap_Q5.keys[j]) == 0)
        {
            search_index = j;
            check_same++;
        }
    }
    if(check_same == 1)
    {
        printf("%s, %s, %s, %s, %s, %s, %s \n", smap_Q5.svalues[search_index].name,smap_Q5.svalues[search_index].name,
            smap_Q5.svalues[search_index].gender, smap_Q5.svalues[search_index].city,
            smap_Q5.svalues[search_index].dept, smap_Q5.svalues[search_index].gpa,
            smap_Q5.svalues[search_index].height, smap_Q5.svalues[search_index].weight);
    }
    else if (check_same == 2)
    {
        printf("이 키는 중복입니다.");
    }

    else
    {
        printf("입력하신 키는 map에 없습니다.");
    }
    
}

int main() 
{
    FILE *fp;
    char line[256];  // 최대 문자열 길이
    int num_records = 0;
    sset my_sset;       // 집합 선언
    sinfo temp;
    smap my_smap_Q3;
    smap my_smap_Q4;
    int check_same = 0;
    smap_Q5 smap_Q5;

    // Open file for reading
    fp = fopen("list.txt", "r+t");
    if (fp == NULL) 
    {
        printf("파일을 열 수 없습니다. \n");
        return 0;
    }

    // 파일 읽기
    while (fgets(line, sizeof(line), fp)) 
    {
        sscanf(line, "%s%s%s%s%s%s%s", temp.name, temp.gender, temp.city, temp.dept, temp.gpa, temp.height, temp.weight);
        //printf("%s %s\n",temp.name, temp.weight);
        if (my_sset.count == 0)
        {
            my_sset.svalues[0] = temp; // 추가할 위치에 추가
        }
        
        for(int j = 0; j <= my_sset.count; j++)
        {
            if(strcmp(temp.name, my_sset.svalues[j].name) == 0)
            {
                check_same = 1;
                continue;
            }
        }
        if (check_same == 0) // 중복 아닌 경우 -- 바로 추가(삽입)
        {
            int index = 0;   // while에서 쓸 루프제어변수, 추가할 위치를 가리킴
            while(index < my_sset.count) 
            {
                if(strcmp(my_sset.svalues[index].name,temp.name) >= 0)
                {
                    for(int index2 = my_sset.count - 1; index2 > index; index2-- )  // 뒤로 밀기
                        my_sset.svalues[index2] = my_sset.svalues[index2 - 1];
                    my_sset.svalues[index] = temp; // 추가할 위치에 추가
                    printf("%s %s\n", my_sset.svalues[index].name,  my_sset.svalues[index].weight);
                    break;
                }
            }
        }
    }

    // for (int i = 0; i < my_sset.count; i++)
    // {
    //     printf("%s, %s, %s, %s, %s, %s, %s \n", my_sset.svalues[i].name,my_sset.svalues[i].name,
    //     my_sset.svalues[i].gender, my_sset.svalues[i].city,
    //     my_sset.svalues[i].dept, my_sset.svalues[i].gpa,
    //     my_sset.svalues[i].height, my_sset.svalues[i].weight);
    // }
    
    // q1. 김문희가 사는곳
    
    Q1(my_sset);
    printf("============== process Q1 is good ===============\n");

    // q2. 천하은보다 성적이 높은사람은 몇 명인지
    
    Q2(my_sset);
    printf("============== process Q2 is good ===============\n");

    // q3. 가장 학생이 많은학과는?
    Q3(my_sset, my_smap_Q3);
    printf("============== process Q3 is good ===============\n");

    // q4. 가장 많은 학생이 거주하는 지역 순서대로 지역을 출력하라.
    Q4(my_sset, my_smap_Q4);
    printf("============== process Q4 is good ===============\n");
    
    // q5. 학생들의 이름을 id로 사용할 수 있는가? 
    // x -> 동명이인이 있기 때문에 학생들의 이름을 id로 사용할 수는 없음.
    Q5(my_sset, smap_Q5, "오영");
    printf("============== process Q5 is good ===============\n");
}