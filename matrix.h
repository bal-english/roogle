
#define INDEX(r,c,i,j) i*r + j

void initMatrix(float a[], int r, int c){

  int i, j;
  for(i = 0; i < r; i++){
    for(j = 0; j < c; j++){
      int index = INDEX(r, c, i, j);
      a[index] = rand() % 100 + 1;
    }
  }
}

void printMatrix(float a[], int r, int c){

  printf("\n");
  int i, j;
  for(i = 0; i < r; i++){
    for(j = 0; j < c; j++){
      int index = INDEX(r,c, i, j);
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
