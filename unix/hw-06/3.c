#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
  FILE *fp = fopen(argv[1], "r");

  int n = 0 ;
  int count = 0 ;
  int num = 0 ;
  int total = 0 ;

  while (n = fscanf(fp, "%d", &num) != EOF)
  {
    total += num;
    count++;
  }

  printf("count = %d sum = %d ave = %f\n", count, total, (float) total / (float) count);
  fclose(fp);

  return 0;
}