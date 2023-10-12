#include <stdio.h>

int (*partition)(int *arr, int s, int e);

void arr_element_swap(int *arr, int idx1, int idx2)
{
    int temp = 0; 
    
    temp = arr[idx2];
    arr[idx2] = arr[idx1];
    arr[idx1] = temp;
}

int partition_by_rightmost_pivot(int * arr, int s, int e)
{
    // s : start point, e : end point

    int pivot = arr[e];
    int i = s - 1;

    for (int j = s; j < e; j++)
    {
        if(arr[j] <= pivot)
        {
            i++;
            arr_element_swap(arr, i, j);
        }
    }

    arr_element_swap(arr, i+1, e);
    return i+1;
}

int partition_by_leftmost_pivot(int * arr, int s, int e)
{

}

int partition_by_median_pivot(int * arr, int s, int e)
{

}

int partition_by_my_pivot(int * arr, int s, int e)
{

}

void quick_sort(int * arr, int s, int e)
{
    // 분할 함수는 함수포인터로 선택해서 진행 
    if( s < e )
    {
        int m = (*partition)(arr, s, e);
        quick_sort(arr, s, m-1);
        quick_sort(arr, m+1, e);
    }
}

int main()
{
    int arr[5] = {1,5,3,2,4};
    partition = &partition_by_rightmost_pivot;
    quick_sort(arr, 0, 4);
    for (int i = 0; i < 5; i++) {
        printf("sorted : %d \n",arr[i] );
    }
    
}