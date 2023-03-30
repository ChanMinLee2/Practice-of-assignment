// htoi 16진수를 10진수로 바꾸는 함수. 

#include <stdio.h>
#include <ctype.h>

int htoi(char s[])
{
        int i, n, sign;

        for ( i = 0; isspace(s[i]); i++)
        ;
        sign = (s[i] == '-') ? -1 : 1;
        if ( s[i] == '+' || s[i] == '-')
                i++;
        for (n = 0; isxdigit(s[i]); i++)
        {
                if (isdigit(s[i]))
                        n = 16 * n + (s[i] - '0');
                else if (isupper(s[i]))
                        n = 16 * n + (s[i] - 'A' + 10);
        }
        return sign * n;
}

int main(void)
{
        char h[] = "12AF";

        printf("%s\n", h);
        printf("%x\n", htoi(h));
        printf("%d\n", htoi(h));

        return 0;
}