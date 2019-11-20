
#define INDEX(n,i,j) i*n + j
#include "time.h"

//randomize matrix
void initMatrix(int a[], int n){

  int i, j;
  for(i = 0; i < n; i++){
    for(j = 0; j < n; j++){
      int index = INDEX(n, i, j);
      a[index] = rand() % n;
    }
  }
}

void printMatrix(int a[], int n){

  printf("\n");
  int i, j;
  for(i = 0; i < n; i++){
    for(j = 0; j < n; j++){
      int index = INDEX(n, i, j);
      //printf("Index %d\n", index);
      printf("%d\t", a[index]);
    }
    printf("\n");
  }
  printf("\n");
}
