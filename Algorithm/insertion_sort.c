#include <stdio.h>

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
            input[j+1] = input[j];
            j--;
        }
        
        for(int i = 0; i < count; i++)
        {
            printf("%d ", input[i]);
        }
        
        input[j+1] = key;
    }
}

int main(void)
{
    int array[10] = {
        1,5,9,8,7,6,2,3,4,10
    };

    insertion_sort(array, 10);

    for(int i = 0; i < 10; i++)
    {
        printf("%d\n", array[i]);
    }
}