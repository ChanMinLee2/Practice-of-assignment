#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	int fd, fd1; 

	fd = open("temp.aaa", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(fd == -1) {
		perror("Creat");
		exit(1);
	}

	close(1);

	fd1 = dup(fd);
	printf("fd1 = %d, fd = %d\n", fd1, fd);

	close(fd);
}
