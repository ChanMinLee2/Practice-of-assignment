#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 32

int (*partition)(int *arr, int s, int e);
int compcount = 0;

int median(int num1, int num2, int num3)
{
    if (num1 >= num2 )
    {
        if (num1 >= num3)
        {
            return num1;
        }
        
        else
        {
            return num3;
        }
        
    }

    else 
    {
        if (num2 >= num3)
        {
            return num2;
        }
        
        else
        {
            return num3;
        }
    }
}

int *array_copy(int *input_arr, int size)
{
    int new_arr[size];
    for (int i = 0; i < size; i++)
    {
        new_arr[i] = input_arr[i];
    }
    return &new_arr;
}

void arr_element_swap(int *arr, int idx1, int idx2)
{
    int temp = 0;

    temp = arr[idx2];
    arr[idx2] = arr[idx1];
    arr[idx1] = temp;
}

int partition_by_rightmost_pivot(int *arr, int s, int e)
{
    // s : start point, e : end point

    int pivot = arr[e];
    int i = s - 1;

    for (int j = s; j < e; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            arr_element_swap(arr, i, j);
        }
        compcount++;
    }

    arr_element_swap(arr, i + 1, e);
    return i + 1;
}

int partition_by_leftmost_pivot(int *arr, int s, int e)
{
    // s : start point, e : end point

    int pivot = arr[rand() % 10];
    int i = s - 1;

    for (int j = s; j < e; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            arr_element_swap(arr, i, j);
        }
        compcount++;
    }

    arr_element_swap(arr, i + 1, e);
    return i + 1;
}

int partition_by_median_pivot(int *arr, int s, int e)
{
    // s : start point, e : end point

    int pivot = median(arr[s], arr[s+e/2], arr[e]);
    int i = s - 1;

    for (int j = s; j < e; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            arr_element_swap(arr, i, j);
        }
        compcount++;
    }

    arr_element_swap(arr, i + 1, e);
    return i + 1;
}

int partition_by_my_pivot(int *arr, int s, int e)
{
    int pivot = 
    int i = s - 1;

    for (int j = s; j < e; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            arr_element_swap(arr, i, j);
        }
        compcount++;
    }

    arr_element_swap(arr, i + 1, e);
    return i + 1;
}

void quick_sort(int *arr, int s, int e)
{
    // 분할 함수는 함수포인터로 선택해서 진행
    if (s < e)
    {
        int m = (*partition)(arr, s, e);
        quick_sort(arr, s, m - 1);
        quick_sort(arr, m + 1, e);
    }
}

int main()
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
        small_sorted_arr[i] = i + 100;
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

    // version 1
    printf("quick sort version 1\n");

    // case 1-1 : sorted small size
    start_time = clock();

    partition = &partition_by_rightmost_pivot;
    quick_sort(small_sorted_arr, 0, 31);

    printf("sorted : [ ");
    for (int i = 0; i < 32; i++)
    {
        printf("%d, ", small_sorted_arr[i]);
    }
    printf("]\n");

    printf("compcount : %d \n", compcount);

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("총 실행 시간: %f 초\n", cpu_time_used);

    // case 1-2 : randomly ordered small size
    start_time = clock();

    partition = &partition_by_rightmost_pivot;
    quick_sort(small_random_arr, 0, 31);

    printf("sorted : [ ");
    for (int i = 0; i < 32; i++)
    {
        printf("%d, ", small_random_arr[i]);
    }
    printf("]\n");

    printf("compcount : %d \n", compcount);

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("총 실행 시간: %f 초\n", cpu_time_used);

    // case 2 : randomly ordered large size
    start_time = clock();

    partition = &partition_by_rightmost_pivot;
    quick_sort(large_arr, 0, 1023);

    printf("sorted : [ ");
    for (int i = 0; i < 1024; i++)
    {
        printf("%d, ", large_arr[i]);
    }
    printf("]\n");

    printf("compcount : %d \n", compcount);

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("총 실행 시간: %f 초\n", cpu_time_used);
}