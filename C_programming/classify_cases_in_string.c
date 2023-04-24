#include <stdio.h>

int main(void)
{
    int index = 0;
    char c;
    int i,other = 0,AS_array[132];
    
    for( i = 'A'; i <= 'z'; i++ )
    {
        AS_array[i] = 0;
    }

    while((c = getchar()) != EOF )
    {
        if (c == '\n')
        {
            break;
        }
        
        if( c >= 'A' && c <= 'z')
        {
            AS_array[c]++;
        }

        else
        {
            other++;
        }
    }
    

    for(index = 'A'; index <='Z'; index++)
    {
        if (AS_array[index] != 0 || AS_array[index + 32] != 0)
        {
            printf("%c/%c count : %d\n", index, index+32, AS_array[index] + AS_array[index + 32]);
        }
        
    }
    printf("Other: %d", other);
    
    

}