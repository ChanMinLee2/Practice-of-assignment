#include <stdio.h>

int main(void)
{
	char x = 'A';
	int count = 1;

	while( x >= 'A' && x <= 'Z')
	{
		if (count % 6 == 0)
		{
			printf("%c%c\n",x, x+32);
			count++;
			x++;
		}
		else
		{
			printf("%c%c ",x, x+32);
			count++;
			x++;
		}
	}
	return 0;
}
