#include <stdio.h>

void merge(int * arr, int s, int m, int e)
{
    // s : start point, m : mid point, e : end point

    int n1 = m - s + 1;
    int n2 = e - m; 
    int left_arr[n1+1]; 
    int right_arr[n2+1];

    for (int i = 0; i < n1; i++)
    {
        left_arr[i] = arr[s + i - 1];
    }
    
    for (int j = 0; j < n2; j++)
    {
        right_arr[j] = arr[m + j];
    }

    left_arr[n1] = 2147483647; // 정수형 최댓값
    right_arr[n2] = 2147483647;

    int idx_left = 0; // ppt상 i
    int idx_right = 0; // ppt상 j

    for (int k = s; k < e; k++)
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
    }
}