#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compcount = 0;

void insertion_sort(int * input, int count)
{
    int key = 0;
    int j = 0;
    
    for(int i = 1; i < count; i++)
    {
        key = input[i];
        
        j = i - 1; 
        printf(" %d  %d  %d\n", key,j,input[i]);
        while( j >= 0 && input[j] > key)
        {
            compcount++;
            input[j+1] = input[j];
            j--;
        }
        compcount++;

        //for(int i = 0; i < count; i++)
        //{
        //    printf("%d ", input[i]);
        //}
        
        input[j+1] = key;
    }
}

int main(void)
{
    // 프로그램 실행 시간 기록을 위한 변수 선언
    clock_t start_time, end_time;
    double cpu_time_used;

    // 정렬할 배열 케이스 별로 선언 , 각 array는 모두 1~1000 사이의 숫자를 가질 수 있다. 
    int large_arr[1024];
    int small_sorted_arr[32];
    int small_random_arr[32];

    // 현재 시간을 시드로 사용하여 난수 발생기 초기화
    srand(time(0));

    // case 1 : small size array
    // 1-1 : sorted array , 100~131 
    for (int i = 0; i < 32; i++)
    {
        small_sorted_arr[i] = i+100;
    }
    // 1-2 : random ordered array
    for (int i = 0; i < 32; i++)
    {
        small_random_arr[i] = rand() % 1000 + 1;
    }
    // case 2 : large size array
    for (int i = 0; i < 1024; i++)
    {
        large_arr[i] = rand() % 1000 + 1;
    }

    // 기록 시작 시간
    start_time = clock();

    // 정렬 코드
    insertion_sort(small_random_arr, 32);

    for(int i = 0; i < 32; i++)
    {
        printf("%d : %d\n", i+1 ,small_random_arr[i]);
    }
    printf("compcount : %d \n", compcount);

    // 기록 종료 시간
    end_time = clock();

    // 실행 시간 계산
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("총 실행 시간: %f 초\n", cpu_time_used);
    
}