#include <stdio.h>

void max_heapify(int* arr, int idx)
{
    int left = 2 * idx;
    int right = 2 * idx + 1;
    int largest = 0;
    int heap_size = sizeof(arr)/sizeof(int); 

    if(arr[left] <= heap_size && (arr[left] > arr[idx]))
    {
        largest = left;
    }
    else
    {
        largest = idx;
    }

    if(arr[right] <= heap_size && (arr[right] > arr[largest]))
    {
        largest = right;
    }
    
    if (largest != idx)
    {
        swap(arr[idx], arr[largest]);
        max_heapify(arr, largest);
    }
}

void build_max_heap(int arr[]);

int main()