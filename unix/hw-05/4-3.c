#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){

	int rfd, wfd, n;
	char buf[10];

	rfd = open("linux.txt", O_RDONLY);
	if(rfd == -1){
		perror("read");
		exit(1);
	}

	wfd = open("linux.bak", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(wfd == -1){
		perror("create");
		exit(1);
	}

	while( n = read(rfd, buf, 5) > 0 ){
		if(write(1, buf, n) != n) perror("write");
	}

	if(n==-1) perror("read");

	close(rfd);
	close(wfd);

}
