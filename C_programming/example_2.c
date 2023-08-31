#include <string.h>
#include <stdio.h>

// valiabls can be used by different functions
char array_number1[10];
char array_number2[10];
char operator = '0';
int number1, number2 = 0;
int check_float_1, check_float_2 = 0;  // if number is integer, check_float is 0. else, 1
int result = 0;
int check_end = 0;
char c;

void receive_input(void)
{
    int i = 0;
    check_end = 0;

    // do need to reset array??  
    while((c = getchar()) != '\n' || c != EOF)
    {
        if(operator == '0') // if operator value exist, don't insert to number1      
            array_number1[i++] = c; // store string number1
            printf("%s\n", array_number1);

        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
            operator = c;     // store character operator

        if(operator != '0')
            array_number2[i++] = c; // store string number2
            printf("%s\n",array_number2);
    }
    if ( c == 'EOF' ) // if it is EOF, end directly
        {
            check_end = 1;
            return;
        }

}

void string_to_number(char string1[], char string2[])
{

    // devide cases of 1)float 2)intaeger
    float number1_decimal , number2_decimal = 0.0;
    int i,j = 0;

    check_float_1 = 0;    // when into new loop, it needs to be reset
    check_float_2 = 0;
    int number1 = (int)number1;
    number1 = 0;
    int number2 = (int)number2;
    number2 = 0;

    while ( string1[i] != 'EOF' ) // processing string to number
    {
        if(check_float_1 == 0)
            number1 = 10 * number1 + (string1[i] - '0');

        if(string1[i] == '.' || check_float_1 == 1)
        {
            check_float_1 = 1;
            number1_decimal = 0.1 * number1_decimal + (string1[i] - '0');
        }
    }


    for ( j = 0; string2[j] != 'EOF'; j++ ) // processing string to number
    {
        if(check_float_2 == 0)
            number2 = 10 * number2 + (string2[j] - '0');

        if(string2[j] == '.' || check_float_2 == 1)
        {
            check_float_2 = 1;
            number2_decimal = 0.1 * number2_decimal + (string2[j] - '0');
        }
    }

    if(check_float_1 == 1)
    {
        float number1 = (float)number1;
        number1 = number1 + number1_decimal ;
        printf("%2.6f", number1);
    }

    if(check_float_2 == 1)
    {
        float number2 = (float)number2;
        number2 = number2 + number2_decimal;
    }
        
}



void calculator(char operator)
{
// use string_to_number function
// switch-case use for operator

    switch(operator)
    {
        int result = (int) result;

        case '+' :
            if(check_float_1 == 0)
                {
                    result = number1 + number2;
                    printf("%d\n",result);
                }
            else
                {
                    float result = (float) result;
                    result = number1 + number2;
                    printf("%2.6f\n",result);
                }
            break;

        case '-' :
            if(check_float_1 == 0)
            {
                result = number1 - number2;
                printf("%d\n", result);
            }
            else
            {
                float result = (float) result;
                result = number1 + number2;
                printf("%2.6f\n", result);
            }
            break;

        case '*' :
            if(check_float_1 == 0)
            {
                result = number1 * number2;
                printf("%d\n", result);
            }
            else
            {
                float result = (float) result;
                result = number1 * number2;
                printf("%2.6f\n", result);
            }
            break;

        case '/' :
            if(check_float_1 == 0)
            {
                result = number1 / number2;
                printf("%d\n", result);
            }
            else
            {
                float result = (float) result;
                result = number1 / number2;
                printf("%2.6f\n", result);
            }
            break;

        case '%' :
        if(check_float_1 == 0)
        {
            result = number1 % number2;
            printf("%d\n", result);
        }
        break;
        //else
        // (float)result = number1 % number2;
        // printf("%2.6f\n", result);
    }

}

int main(void)
{
    int process_count = 0;
    while (process_count < 200)
    {
        receive_input();
        if( check_end == 1 )
            break;
        string_to_number(array_number1, array_number2);
        calculator(operator);
        process_count++;
    }
}   