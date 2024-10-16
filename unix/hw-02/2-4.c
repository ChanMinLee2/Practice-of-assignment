#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int n;
	// getopt 함수에서 관리하는 전역변수를 가져와서 씀
	extern char *optarg;
	extern int optind;

	// getopt loop에서 얻어지는 결과값을 저장할 변수
	long r;
	
	// getopt loop, getopt 함수의 반환 저장 후 특정 옵션(a,m)인지 확인
	// 'a:' 인자를 추가로 받는 옵션 a
	// 'm:' 인자를 추가로 받는 옵션 m
	while((n=getopt(argc, argv, "a:m:")) != -1){
		switch(n){
			// 옵션이 a인 경우 r = 0으로 초기화
			// for loop를 돌면서 나머지 인자들을 모두 r에 더함
			case 'a':
				r = 0;
				for(--optind; optind < argc; optind++)
					r = r + atol(argv[optind]);
			break;
			// 옵션이 m인 경우 r = 1으로 초기화
			// for loop를 돌면서 나머지 인자들을 모두 r에 곱함
			case 'm':
				r = 1;
				for(--optind; optind < argc; optind++)
					r = r * atol(argv[optind]);
			break;
		}
		// 결과 출력
		printf("res = %ld\n", r);
	}
}
