#include <stdio.h>

// heap size는 배열 크기 - 1 

void arr_element_swap(int *arr, int idx1, int idx2)
{
    int temp = 0; 
    
    temp = arr[idx2];
    arr[idx2] = arr[idx1];
    arr[idx1] = temp;
}

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
    int test[11] = {0, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

    heap_sort(test, 10);
    for (int i = 1; i <= 10; i++)
    {
        printf("%d\n", test[i]);
    }

}