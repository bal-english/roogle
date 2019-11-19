
#define INDEX(n,i,j) i*n + j

void initMatrix(float a[], int n){

  int i, j;
  for(i = 0; i < n; i++){
    for(j = 0; j < n; j++){
      int index = INDEX(n, i, j);
      a[index] = rand() % 100 + 1;
    }
  }
}

void printMatrix(float a[], int n){

  printf("\n");
  int i, j;
  for(i = 0; i < n; i++){
    for(j = 0; j < n; j++){
      int index = INDEX(n, i, j);
      //printf("Index %d\n", index);
      printf("%.2f\t", a[index]);
    }
    printf("\n");
  }
  printf("\n");
}

void printVector(float v[], int size){

  printf("\n");

  int i;
  for(i = 0; i < size; i++){
    printf("%.2f\n", v[i]);
  }
  printf("\n");

}
