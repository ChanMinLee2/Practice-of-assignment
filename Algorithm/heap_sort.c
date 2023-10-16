#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compcount = 0;

void arr_element_swap(int *arr, int idx1, int idx2)
{
    int temp = 0; 
    
    temp = arr[idx2];
    arr[idx2] = arr[idx1];
    arr[idx1] = temp;
}

// heap size = 배열 사이즈 - 1
void max_heapify(int* arr, int idx, int heap_size)
{
    int left = 2 * idx;
    int right = 2 * idx + 1;
    int largest = 0; 

    if(left <= heap_size && (arr[left] > arr[idx]))
    {
        largest = left;
    }

    else
    {
        largest = idx;
    }

    compcount++;

    if(right <= heap_size && (arr[right] > arr[largest]))
    {
        largest = right;
    }
    
    if (largest != idx)
    {
        arr_element_swap(arr, idx, largest);
        max_heapify(arr, largest, heap_size);
        //printf("check - %d\n", arr[1]);
    }

    compcount++;
}

void build_max_heap(int* arr, int heap_size)
{
    for (int i = heap_size/2; i > 0; i--)
    {
        //printf("%d's build start\n", i);
        max_heapify(arr, i, heap_size);
        //printf("%d's build end\n", i);
    }
}

void heap_sort(int * arr, int heap_size)
{
    build_max_heap(arr,heap_size);

    for (int i = heap_size; i >= 2; i--)
    {
        arr_element_swap(arr,1,i);
        heap_size--;
        max_heapify(arr, 1, heap_size);
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

    // case 1 정렬 
    heap_sort(small_sorted_arr, 31);
    for (int i = 1; i <= 31; i++)
    {
        printf("%d\n", small_sorted_arr[i]);
    }
    printf("compcount : %d \n", compcount);

    // 기록 종료 시간
    end_time = clock();

    // 실행 시간 계산
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("총 실행 시간: %f 초\n", cpu_time_used);
    
}