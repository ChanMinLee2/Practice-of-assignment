#include <stdio.h>

int main(void)
{
    int fahr, celsius = 0;
    int lower = 0;
    int step = 10;

    printf("섭씨온도로 변경할 화씨온도를 입력하세요 (0 ~ 100 ) : ");
    scanf("%d", &fahr);

    while(fahr > lower)
    {
        celsius = 5 * (fahr - 32) / 9;
        printf("%d \n", celsius);
        
        fahr -= step; 
    }

    return 0;
    
}