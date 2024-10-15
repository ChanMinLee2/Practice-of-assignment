#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)

{
	// access 함수로 linux.txt라는 파일을 접근	
	// F_OK라는 마스크 값으로 위 파일이 존재하는 지를 파악 (성공 0, 실패 -1) 
	if (access("linux.txt", F_OK) == -1){
		// 실패 시, stderr에 linux.txt로 시작하는 에러메시지 출력 후
		// 에러로 인한 강제종료의 의미인 exit(1)으로 프로세스를 종료
		perror("linux.txt");
		exit(1);
	}
	return 0;
}

