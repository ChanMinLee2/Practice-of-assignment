#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int ARR_SIZE = 0;  
int compcount = 0;

//##############################################################
// insertion sort
void insertion_sort(int * input, int count)
{
    int key = 0;
    int j = 0;
    
    for(int i = 1; i < count; i++)
    {
        key = input[i];
        
        j = i - 1; 
        //printf(" %d  %d  %d\n", key,j,input[i]);
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

//##############################################################
// heap sort
void arr_element_swap(int *arr, int idx1, int idx2)
{
    int temp = 0; 
    
    temp = arr[idx2];
    arr[idx2] = arr[idx1];
    arr[idx1] = temp;
}

// 배열의 크기를 늘려서 배열을 한 칸씩 뒤로 이동시키는 함수
int* shiftArray(int arr[], int size) {
    int newSize = size + 1; 
    int* shiftedArray = (int*)malloc(newSize * sizeof(int));  // 새로운 배열 동적 할당

    if (shiftedArray == NULL) {
        // 동적 할당 실패
        fprintf(stderr, "메모리 할당 오류\n");
        exit(1);
    }

    // 기존 배열의 요소를 새로운 배열로 복사
    for (int i = 0; i < size; i++) {
        shiftedArray[i + 1] = arr[i];
    }

    // 기존 배열의 내용을 늘린 배열의 첫 번째 요소 그냥 채우기
    shiftedArray[0] = 0;  

    return shiftedArray;
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

//##############################################################
// merge sort
void merge(int * arr, int s, int m, int e)
{
    // s : start point, m : mid point, e : end point

    int n1 = m - s + 1; // left array's size
    int n2 = e - m;     // right array's size
    //printf("n1 : %d, n2 : %d\n\n", n1, n2);
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

//##############################################################
// quick sort

// 이 함수 포인터로 분할 함수를 조정함. 
int (*partition)(int *arr, int s, int e);

int median(int* arr, int num1, int num2, int num3)
{
    if ((arr[num1] <= arr[num2] && arr[num2] <= arr[num3]) || (arr[num3] <= arr[num2] && arr[num2] <= arr[num1]))
    {
        return num2;
    }
    
    else if ((arr[num2] <= arr[num3] && arr[num3] <= arr[num1]) || (arr[num1] <= arr[num3]) && arr[num3] <= arr[num2])
    {
        return num3;
    }
    
    else
    {
        return num1;
    }
}

int *array_copy(const int *input_arr, int size) {
    int *new_arr = (int *)malloc(size * sizeof(int));
    
    for (int i = 0; i < size; i++) {
        new_arr[i] = input_arr[i];
    }
    
    return new_arr;
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

    int flag = (rand() % (e-s)) + s ;

    arr_element_swap(arr, flag, e);

    return partition_by_rightmost_pivot(arr, s, e);
}

int partition_by_median_pivot(int *arr, int s, int e)
{
    // s : start point, e : end point

    int med = median(arr, s, (s+e)/2 , e);
    
    arr_element_swap(arr, med, e);

    return partition_by_rightmost_pivot(arr, s, e); ;
}

int partition_by_my_pivot(int *arr, int s, int e)
{
    int flag = rand() % (ARR_SIZE-1);
    int pivot = 0;
    if( abs(500 - median(arr, s, (s+e)/2, e)) <= abs(500 - arr[flag]))
    {
        pivot = median(arr, s, (s+e)/2, e);
    }

    else
    {
        pivot = arr[flag];
    }
    compcount++;

    int i = s - 1;

    for (int j = s; j < e; j++)
    {
        if (arr[j] <= arr[pivot])
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
    int scan_case = 0;
    printf("실행할 case number를 입력하세요 : ");
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



    //##############################################################
    // insertion sort
    printf("############ insertion sort ############\n");
    int *arr_insertion;
    compcount = 0;

    if (scan_case == 1 )
    {
        arr_insertion = array_copy(small_sorted_arr, ARR_SIZE);
    }
    else if (scan_case == 2)
    {
        arr_insertion = array_copy(small_random_arr, ARR_SIZE);
    }
    else
    {
        arr_insertion = array_copy(large_arr, ARR_SIZE);
    }

    // 기록 시작 시간
    start_time = clock();

    // 정렬 코드
    insertion_sort(arr_insertion, ARR_SIZE);

    printf("sorted : [");
    for(int i = 0; i < ARR_SIZE; i++)
    {
        printf("%d, ",arr_insertion[i]);
    }
    printf("]\n");
    printf("compcount : %d \n", compcount);

    // 기록 종료 시간
    end_time = clock();

    // 실행 시간 계산
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("총 실행 시간: %f 초\n\n", cpu_time_used);


    //##############################################################
    // heap sort
    printf("############ heap sort ############\n");
    int *arr_heapsort;
    compcount = 0;

    if (scan_case == 1 )
    {
        arr_heapsort = array_copy(small_sorted_arr, ARR_SIZE);
    }
    else if (scan_case == 2)
    {
        arr_heapsort = array_copy(small_random_arr, ARR_SIZE);
    }
    else
    {
        arr_heapsort = array_copy(large_arr, ARR_SIZE);
    }   
    arr_heapsort = shiftArray(arr_heapsort, ARR_SIZE);

    // 기록 시작 시간
    start_time = clock();

    heap_sort(arr_heapsort, ARR_SIZE);
    printf("sorted : [");
    for(int i = 1; i <= ARR_SIZE; i++)
    {
        printf("%d, ", arr_heapsort[i]);
    }
    printf("]\n");
    printf("compcount : %d \n", compcount);

    // 기록 종료 시간
    end_time = clock();

    // 실행 시간 계산
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("총 실행 시간: %f 초\n\n", cpu_time_used);

    //##############################################################
    // merge sort

    printf("############ merge sort ############\n");
    int *arr_mergesort;
    compcount = 0;

    if (scan_case == 1 )
    {
        arr_mergesort = array_copy(small_sorted_arr, ARR_SIZE);
    }
    else if (scan_case == 2)
    {
        arr_mergesort = array_copy(small_random_arr, ARR_SIZE);
    }
    else
    {
        arr_mergesort = array_copy(large_arr, ARR_SIZE);
    }

    // 기록 시작 시간
    start_time = clock(); 
    
    merge_sort(arr_mergesort, 0, ARR_SIZE-1);

    printf("sorted : [ ");
    for (int i = 0; i < ARR_SIZE; i++)
    {
        printf("%d, ", arr_mergesort[i]);
    }
    printf("]\n");

    printf("compcount : %d \n", compcount);
    
    // 기록 종료 시간
    end_time = clock();

    // 실행 시간 계산
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("총 실행 시간: %f 초\n\n", cpu_time_used);
    


    //#######################################################################################
    // quick sort version 1
    printf("quick sort version 1 : right most element \n");

    int *arr_version_1;

    if (scan_case == 1 )
    {
        arr_version_1 = array_copy(small_sorted_arr, ARR_SIZE);
    }
    else if (scan_case == 2)
    {
        arr_version_1 = array_copy(small_random_arr, ARR_SIZE);
    }
    else
    {
        arr_version_1 = array_copy(large_arr, ARR_SIZE);
    }

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
    printf("총 실행 시간: %f 초\n\n", cpu_time_used);
    

    //#######################################################################################
    // quick sort version 2
    printf("quick sort version 2 : random pivot \n");

    int *arr_version_2;
    if (scan_case == 1 )
    {
        arr_version_2 = array_copy(small_sorted_arr, ARR_SIZE);
    }
    else if (scan_case == 2)
    {
        arr_version_2 = array_copy(small_random_arr, ARR_SIZE);
    }
    else
    {
        arr_version_2 = array_copy(large_arr, ARR_SIZE);
    }

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
    printf("총 실행 시간: %f 초\n\n", cpu_time_used);


    //#######################################################################################
    // quick sort version 3
    printf("quick sort version 3 : median of three value \n");

    int *arr_version_3;
    if (scan_case == 1 )
    {
        arr_version_3 = array_copy(small_sorted_arr, ARR_SIZE);
    }
    else if (scan_case == 2)
    {
        arr_version_3 = array_copy(small_random_arr, ARR_SIZE);
    }
    else
    {
        arr_version_3 = array_copy(large_arr, ARR_SIZE);
    }

    start_time = clock();

    partition = &partition_by_median_pivot;
    quick_sort(arr_version_3, 0, ARR_SIZE-1);

    printf("sorted : [ ");
    for (int i = 0; i < ARR_SIZE; i++)
    {
        printf("%d, ", arr_version_3[i]);
    }
    printf("]\n");

    printf("compcount : %d \n", compcount);

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("총 실행 시간: %f 초\n\n", cpu_time_used);


    //#######################################################################################
    // quick sort version 4
    printf("quick sort version 4 : my strategy \n");

    int *arr_version_4;
    if (scan_case == 1 )
    {
        arr_version_4 = array_copy(small_sorted_arr, ARR_SIZE);
    }
    else if (scan_case == 2)
    {
        arr_version_4 = array_copy(small_random_arr, ARR_SIZE);
    }
    else
    {
        arr_version_4 = array_copy(large_arr, ARR_SIZE);
    }

    // case 1-1 : sorted small size
    start_time = clock();

    partition = &partition_by_random_pivot;
    quick_sort(arr_version_4, 0, ARR_SIZE-1);

    printf("sorted : [ ");
    for (int i = 0; i < ARR_SIZE; i++)
    {
        printf("%d, ", arr_version_4[i]);
    }
    printf("]\n");

    printf("compcount : %d \n", compcount);

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("총 실행 시간: %f 초\n\n", cpu_time_used);

}