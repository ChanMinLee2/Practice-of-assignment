#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 32

// �� �Լ� �����ͷ� ���� �Լ��� ������. 
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

int *array_copy(const int *input_arr, int size) {
    int *new_arr = (int *)malloc(size * sizeof(int));
    
    for (int i = 0; i < size; i++) {
        new_arr[i] = input_arr[i];
    }
    
    return new_arr;
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

int partition_by_random_pivot(int *arr, int s, int e)
{
    // s : start point, e : end point

    int flag = rand() % (ARR_SIZE-1) ;
    int pivot = arr[flag];
    int i = s - 1;

    arr_element_swap(arr, flag, e);

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
    int flag = rand() % (ARR_SIZE-1);
    int pivot = 0;
    if( abs(500 - median(arr[s], arr[s+e/2], arr[e])) <= abs(500 - arr[flag]))
    {
        pivot = median(arr[s], arr[s+e/2], arr[e]);
    }

    else
    {
        pivot = arr[flag];
    }
    compcount++;

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
    // ���� �Լ��� �Լ������ͷ� �����ؼ� ����
    if (s < e)
    {
        int m = (*partition)(arr, s, e);
        quick_sort(arr, s, m - 1);
        quick_sort(arr, m + 1, e);
    }
}

int main()
{
    // ���α׷� ���� �ð� ����� ���� ���� ����
    clock_t start_time, end_time;
    double cpu_time_used;

    // ������ �迭 ���̽� ���� ���� , �� array�� ��� 1~1000 ������ ���ڸ� ���� �� �ִ�.
    int large_arr[1024];
    int small_sorted_arr[32];
    int small_random_arr[32];

    // ���� �ð��� �õ�� ����Ͽ� ���� �߻��� �ʱ�ȭ
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
    printf("quick sort version 1 : right most element \n");

    int *arr_version_1;
    arr_version_1 = array_copy(small_sorted_arr, ARR_SIZE);

    // case 1-1 : sorted small size
    start_time = clock();

    partition = &partition_by_rightmost_pivot;
    quick_sort(arr_version_1, 0, ARR_SIZE-1);

    printf("sorted : [ ");
    for (int i = 0; i < ARR_SIZE; i++)
    {
        printf("%d, ", arr_version_1[i]);
    }
    printf("]\n");

    printf("compcount : %d \n", compcount);

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("�� ���� �ð�: %f ��\n", cpu_time_used);
    
    // version 2
    printf("quick sort version 2\n");

    int *arr_version_2;
    arr_version_2 = array_copy(small_sorted_arr, ARR_SIZE);

    // case 1-1 : sorted small size
    start_time = clock();

    partition = &partition_by_random_pivot;
    quick_sort(arr_version_2, 0, ARR_SIZE-1);

    printf("sorted : [ ");
    for (int i = 0; i < ARR_SIZE; i++)
    {
        printf("%d, ", arr_version_2[i]);
    }
    printf("]\n");

    printf("compcount : %d \n", compcount);

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("�� ���� �ð�: %f ��\n", cpu_time_used);

    // version 3
    printf("quick sort version 3 : median of three value \n");

    int *arr_version_3;
    arr_version_3 = array_copy(small_sorted_arr, ARR_SIZE);

    start_time = clock();

    partition = &partition_by_median_pivot;
    quick_sort(arr_version_2, 0, ARR_SIZE-1);

    printf("sorted : [ ");
    for (int i = 0; i < ARR_SIZE; i++)
    {
        printf("%d, ", arr_version_3[i]);
    }
    printf("]\n");

    printf("compcount : %d \n", compcount);

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("�� ���� �ð�: %f ��\n", cpu_time_used);

    // version 4
    printf("quick sort version 4 : my strategy \n");

    int *arr_version_4;
    arr_version_4 = array_copy(small_sorted_arr, ARR_SIZE);

    // case 1-1 : sorted small size
    start_time = clock();

    partition = &partition_by_random_pivot;
    quick_sort(arr_version_4, 0, 31);

    printf("sorted : [ ");
    for (int i = 0; i < ARR_SIZE; i++)
    {
        printf("%d, ", arr_version_4[i]);
    }
    printf("]\n");

    printf("compcount : %d \n", compcount);

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("�� ���� �ð�: %f ��\n", cpu_time_used);

}