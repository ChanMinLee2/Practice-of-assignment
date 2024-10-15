#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	// char type의 포인터 변수 선언
	char *str;

	// malloc을 통해 (char size) * 20 만큼 동적 메모리 할당 
	str = malloc(sizeof(char) * 20);
	
	// str 포인터 변수에 문자열 복사 후 저장 및 출력
	strcpy(str, "Hello");
	printf("%s\n", str);
	strcpy(str, "Good morning");
	printf("%s\n", str);

	// str 포인터 변수 메모리 반환 및 종료
	free(str);
	return 0;
}
