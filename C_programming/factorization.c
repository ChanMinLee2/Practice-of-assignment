#include <stdio.h>

int main(void)
{
        int number = 0;
        int i = 0;
        int check_devide = 0;

        printf("input integer: ");
        scanf("%d", &number);

        int devider[100];
        int index = 0;
        int size = number;

        for( i = 2; i*i <= number; i++)
        {
                
                while (number % i == 0)
                {
                        check_devide++;
                        devider[index++] = i;
                        number /= i;
                        //printf("%d\n", i);
                }
        }
        if (number > 1)
        {
                check_devide++;
                devider[index++] = number;
                printf("%d\n", number);
        }

        if(check_devide == 0)
                printf("%d", number);
        else
        {
                for(index = 0; index < check_devide; index++)
                {
                        if(index == (check_devide-1))
                                printf("%d", devider[index]);
                        else   
                                printf("%d * ",devider[index]);
                }
        }
        return 0;
}


