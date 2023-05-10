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
    char keys[MAX_NUM][MAX_NUM];
    sinfo svalues[MAX_NUM]; 
    int count;
};

// 그리고 3,4번 접근할 구조체 타입 map선언. 이걸로는 키 : 값 구조로 사용 

// 아마 키에는 학과 값에는 집합 또는 학과의 학생 수 이렇게 넣을듯?

void set_print(struct sset *mySet) {
    for (int i = 0; i < mySet -> count; i++) {
        printf("%s ", mySet -> svalues[i].name);
        printf("%s ", mySet -> svalues[i].gender);
        printf("%s ", mySet -> svalues[i].city);  
        printf("%s ", mySet -> svalues[i].dept);  
        printf("%s ", mySet -> svalues[i].gpa);  
        printf("%s ", mySet -> svalues[i].height);  
        printf("%s\n", mySet -> svalues[i].weight);
    }
}

void Q1(sset sset)
{
    for(int i = 0; i < sset.count; i++)
    {
        if(strcmp(sset.svalues[i].name, "김문희") == 0) // 왜 비교가 제대로 안되는거지?
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
        if((atof(sset.svalues[i].gpa)) > atof(chun.gpa)) // 위 for문에서 제대로 받지 못함. 
        {
            count_Q2++;
        }
    }
    printf("천하은보다 성적이 높은사람 수 : %d \n", count_Q2);
}

void Q3(sset sset)
{
    int max = 0; // Q3에서 쓸 최댓값 선언 및 초기화
    smap smap; // Q3에서 쓸 맵 선언

    // smap 초기화
    for (int i = 0; i < MAX_NUM; i++)
    {
        smap.values[i] = 0;
        //printf("%d\n", smap.values[i]);
    }
    smap.count = 0;

    // while 증가연산자
    int process = 0;
    
    // set의 원소들을 순차적으로 읽는 while loop 
    while (process < sset.count )
    {
        if (process == 0) // 첫 추가
        {
            strcpy(smap.keys[process], sset.svalues[process].dept);
            smap.values[smap.count] = 0;
            (smap.values[smap.count])++;
            (smap.count)++;
            process++;
            //printf("first %s %d %d %d\n\n", smap.keys[0] , smap.count, process, sset.count);
        }
        
        else // 첫 추가 이후 (process > 0 일 때)
        {
            // smap의 원소를 제어할 for loop
            for (int i = 0; i <= smap.count; i++) 
            {
                // printf("%s \n", smap.values[process].name);
                
                // process index의 dept가 map의 모든 키와 비교해도 없을 때. >> map 키에 추가해야 함
                if ( i == smap.count && strcmp(smap.keys[i-1], sset.svalues[process].dept) != 0 )
                {
                    strcpy(smap.keys[smap.count], sset.svalues[process].dept);  // 키 추가
                    (smap.values[smap.count])++;                                // 새로운 키의 값 ++
                    smap.count++;  // 키 추가됐음을 count로 셈
                    //printf("%s\n", smap.keys[smap.count]);
                    //printf("good insert new key\n");
                    break;
                }
                // process index의 dept가 map의 한 키와 똑같을 때 >> map 해당하는 키의 값을 ++해야함
                else if ( strcmp(smap.keys[i], sset.svalues[process].dept) == 0 ) // 이게 왜 안걸리지? 김문희
                {
                    (smap.values[i])++;
                    //printf("good increse value\n");
                    break;
                }
                // 위 두가지 경우가 아님 = 겹치는 키도 없지만, 아직 map의 키를 다 확인하지는 못 함.
            }

            process++; // while loop를 컨트롤하는 process를 1 증가시킴. (loop 1회)
        }
    }

    // for (int i = 0; i < smap.count; i++)
    // {
    //     printf("%d\n", smap.values[i]);
    // }
    
    max = smap.values[0]; // smap의 첫 값부터 비교시작.
    
    for (int i = 0; i < smap.count; i++)
    {
        if (smap.values[i+1] > smap.values[i])
        {
            max = smap.values[i+1];
        }
        
    }

    printf("학생 수가 가장 많은 학과의 학생 수 : %d \n", max);
    
}

void Q4(sset sset, smap smap)
{
    int max = 0; // Q3에서 쓸 최댓값 선언 및 초기화
    smap smap; // Q3에서 쓸 맵 선언

    // smap 초기화
    for (int i = 0; i < MAX_NUM; i++)
    {
        smap.values[i] = 0;
        //printf("%d\n", smap.values[i]);
    }
    smap.count = 0;

    // while 증가연산자
    int process = 0;
    
    // set의 원소들을 순차적으로 읽는 while loop 
    while (process < sset.count )
    {
        if (process == 0) // 첫 추가
        {
            strcpy(smap.keys[process], sset.svalues[process].dept);
            smap.values[smap.count] = 0;
            (smap.values[smap.count])++;
            (smap.count)++;
            process++;
            //printf("first %s %d %d %d\n\n", smap.keys[0] , smap.count, process, sset.count);
        }
        
        else // 첫 추가 이후 (process > 0 일 때)
        {
            // smap의 원소를 제어할 for loop
            for (int i = 0; i <= smap.count; i++) 
            {
                // printf("%s \n", smap.values[process].name);
                
                // process index의 dept가 map의 모든 키와 비교해도 없을 때. >> map 키에 추가해야 함
                if ( i == smap.count && strcmp(smap.keys[i-1], sset.svalues[process].dept) != 0 )
                {
                    strcpy(smap.keys[smap.count], sset.svalues[process].dept);  // 키 추가
                    (smap.values[smap.count])++;                                // 새로운 키의 값 ++
                    smap.count++;  // 키 추가됐음을 count로 셈
                    //printf("%s\n", smap.keys[smap.count]);
                    //printf("good insert new key\n");
                    break;
                }
                // process index의 dept가 map의 한 키와 똑같을 때 >> map 해당하는 키의 값을 ++해야함
                else if ( strcmp(smap.keys[i], sset.svalues[process].dept) == 0 ) // 이게 왜 안걸리지? 김문희
                {
                    (smap.values[i])++;
                    //printf("good increse value\n");
                    break;
                }
                // 위 두가지 경우가 아님 = 겹치는 키도 없지만, 아직 map의 키를 다 확인하지는 못 함.
            }

            process++; // while loop를 컨트롤하는 process를 1 증가시킴. (loop 1회)
        }
    }

    // for (int i = 0; i < smap.count; i++)
    // {
    //     printf("%d\n", smap.values[i]);
    // }
    
    max = smap.values[0]; // smap의 첫 값부터 비교시작.
    
    for (int i = 0; i < smap.count; i++)
    {
        if (smap.values[i+1] > smap.values[i])
        {
            max = smap.values[i+1];
        }
        
    }
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
        printf("%s, %s, %s, %s, %s, %s, %s \n", smap_Q5.svalues[search_index].name,
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
        check_same = 0; 
        sscanf(line, "%s%s%s%s%s%s%s", temp.name, temp.gender, temp.city, temp.dept, temp.gpa, temp.height, temp.weight);
        if (my_sset.count == 0)
        {
            my_sset.svalues[0] = temp; // 추가할 위치에 추가
            my_sset.count++; 
            continue;
        }
        for(int j = 0; j <= my_sset.count; j++)
        {
            if(strcmp(temp.name, my_sset.svalues[j].name) == 0)
            {
                check_same = 1;
            }
        }
        if (check_same == 0) // 중복 아닌 경우 -- 바로 추가(삽입)
        {
            int index = 0;   // while에서 쓸 루프제어변수, 추가할 위치를 가리킴
            while(index <= my_sset.count) 
            {
                if (index == my_sset.count-1)
                {
                    if ((index + 1) < MAX_NUM )
                    {
                        my_sset.svalues[index+1] = temp;
                    }

                    else
                    {
                        printf("정보를 더 이상 추가할 수 없습니다.");
                    }
                    
                }
                
                if(strcmp(my_sset.svalues[index].name,temp.name) >= 0 ) // 0번쨰 index에 추가될 때
                {
                    for(int index2 = my_sset.count; index2 >= index; index2-- )  //  맨 끝에 추가될때를 생각해서 여기 말고 밑에를 고침
                        my_sset.svalues[index2 + 1] = my_sset.svalues[index2];   // 뒤로 밀기
                    my_sset.svalues[index] = temp; // 추가할 위치에 추가 
                    my_sset.count++; // 증가 연산자
                    break;
                }
                index++; // 증가 연산자
            }
        }
    }
    
    // q1. 김문희가 사는곳

    set_print(&my_sset);
    Q1(my_sset);
    printf("============== process Q1 is good ===============\n");

    // q2. 천하은보다 성적이 높은사람은 몇 명인지
    
    Q2(my_sset);
    printf("============== process Q2 is good ===============\n");

    // q3. 가장 학생이 많은학과는?
    Q3(my_sset);
    printf("============== process Q3 is good ===============\n");

    // q4. 가장 많은 학생이 거주하는 지역 순서대로 지역을 출력하라.
    Q4(my_sset, my_smap_Q4);
    printf("============== process Q4 is good ===============\n");
    
    // q5. 학생들의 이름을 id로 사용할 수 있는가? 
    // x -> 동명이인이 있기 때문에 학생들의 이름을 id로 사용할 수는 없음.
    Q5(my_sset, smap_Q5, "오영");
    printf("============== process Q5 is good ===============\n");
}