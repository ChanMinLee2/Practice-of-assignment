#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "quick_sort.c"

int ARR_SIZE = 0;

int compcount = 0;
// compcount는 조건 비교를 제외하고 배열 내부원소끼리 비교만 체크한다. 

void merge(int * arr, int s, int m, int e)
{
    // s : start point, m : mid point, e : end point

    int n1 = m - s + 1; // left array's size
    int n2 = e - m;     // right array's size
    printf("n1 : %d, n2 : %d\n\n", n1, n2);
    int left_arr[n1+1]; 
    int right_arr[n2+1];

    // first for loop - copy arr values to left
    for (int i = 0; i < n1; i++) 
    {
        left_arr[i] = arr[s + i];
        //printf("left i : %d - left_arr[i] : %d - arr[s+i] : %d\n", i, left_arr[i], arr[s+i]);
    }
    
    // second for loop - copy arr values to right
    for (int j = 0; j < n2; j++)
    {
        right_arr[j] = arr[m + j + 1];
        //printf("right %d : %d : %d \n", j, right_arr[j], arr[m+j+1]);
    }

    left_arr[n1] = 2147483647; // 정수형 최댓값 ()
    right_arr[n2] = 2147483647;

    int idx_left = 0; // ppt상 i
    int idx_right = 0; // ppt상 j

    for (int k = s; k <= e; k++)
    {
        if (left_arr[idx_left] <= right_arr[idx_right])
        {
            arr[k] = left_arr[idx_left];
            idx_left++;
        }

        else
        {
            arr[k] = right_arr[idx_right];
            idx_right++;
        }
        compcount++;
    }
}

void merge_sort(int * arr, int s, int e)
{
    if( s < e )
    {
        int m = (s+e)/2;
        merge_sort(arr, s, m);
        merge_sort(arr, m+1, e);
        merge(arr,s,m,e);
    }
}

int main(void)
{
    int scan_case = 0;
    printf("실행할 quick sort case number를 입력하세요 : ");
    scanf("%d", &scan_case);
    
    if (scan_case == 1 || scan_case == 2)
    {
        ARR_SIZE = 32;
    }
    else if(scan_case == 3)
    {
        ARR_SIZE = 1024;
    }
    else
    {
        printf("1,2,3 중 입력해주세요\n");
        return 0;
    }

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

    //#######################################################################################
    // case 1

    // 기록 시작 시간
    start_time = clock();

    if (scan_case == 1)
    {
        compcount = 0;
        ARR_SIZE = 32;
        printf("small sorted array sort as merge \n");
        merge_sort(small_sorted_arr, 0, ARR_SIZE-1);

        printf("sorted : [ ");
        for (int i = 0; i < ARR_SIZE; i++)
        {
            printf("%d, ", small_sorted_arr[i]);
        }
        printf("]\n");

        // 기록 종료 시간
        end_time = clock();

        // 실행 시간 계산
        cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("총 실행 시간: %f 초\n", cpu_time_used);
    }

    //#######################################################################################
    // case 2
    
    // 기록 시작 시간
    start_time = clock();

    if (scan_case == 2)
    {
        compcount = 0;
        ARR_SIZE = 32;
        printf("small random array sort as merge \n");
        merge_sort(small_random_arr, 0, ARR_SIZE-1);

        printf("sorted : [ ");
        for (int i = 0; i < ARR_SIZE; i++)
        {
            printf("%d, ", small_random_arr[i]);
        }
        printf("]\n");

        // 기록 종료 시간
        end_time = clock();

        // 실행 시간 계산
        cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("총 실행 시간: %f 초\n", cpu_time_used);
    }
    
    //#######################################################################################
    // case 3
    
    // 기록 시작 시간
    start_time = clock();

    if (scan_case == 3)
    {
        compcount = 0;
        ARR_SIZE = 1024;
        printf("large array sort as merge \n");
        merge_sort(large_arr, 0, ARR_SIZE-1);

        printf("sorted : [ ");
        for (int i = 0; i < ARR_SIZE; i++)
        {
            printf("%d, ", large_arr[i]);
        }
        printf("]\n");

        // 기록 종료 시간
        end_time = clock();

        // 실행 시간 계산
        cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("총 실행 시간: %f 초\n", cpu_time_used);
    }
}