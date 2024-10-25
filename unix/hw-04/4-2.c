#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

 

int main() {
    // dp는 디렉토리 포인터로 디렉토리 스트림을 저장하는 데 씀
    DIR *dp;
    
    // dent는 디렉토리 엔티티 포인터로 디렉토리 구조체 주소를 저장하는 데 씀 
    struct dirent *dent;

 
    // "." 현재 경로의 디렉토리 스트림을 열어서 dp에 저장함
    dp = opendir(".");

 
    // readdir(dp) 디렉토리 포인터로 디렉토리 스트림을 순회, 
    // 파일또는 디렉토리가 없으면 종료
    // 디렉토리 엔티티에 파일 정보를 받아옴
    while ((dent = readdir(dp))) {

	// 파일 이름 출력
        printf("Name : %s ", dent->d_name);
	// inode번호 출력
        printf("Inode : %d\n", (int)dent->d_ino);

    }

 
    // 디렉토리를 다 확인한 다음 디렉토리 스트림 닫기
    closedir(dp);

} 
