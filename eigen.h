

//we disregard my matrix multiplication calculator
//we only do matrix vector products here
//faster to just redo it
void matrvct(int matrix[], float vector[], float product[], int n){

  int i, j;

  for(i = 0; i < n; i++){

    product[i] = 0;

    for(j = 0; j < n; j++){
      float m = matrix[INDEX(n, i, j)], v = vector[j];
      //printf("Multiplying %.2f by %.2f\n", m, v);
      product[i] += (m * v);
    }
    //printf("%d sum: %.2f\n\n", i, product[i]);
  }

}

float findmax(float a[], int msize){

  int i;
  float  maximum = a[0];
  for(i = 0; i < msize; i++){
    if(maximum < a[i]){
      maximum = a[i];
    }
  }

  return maximum;

}

int floatcomp(float a, float b){

  //small float comparison function
  //was not converging in some cases when original == was used

  double epsilon = .01f;
  if(fabs(a - b) < epsilon){
    return 1;
  }

  return 0;
}

int isEqual(float a[], float b[], int size){

  //we just want to see if these vectors are the same
  //no need to worry about indexing

  int i;

/*
  for(i = 0; i < size; i++){
    printf("%d  %.2f  %.2f\n",size, a[i], b[i]);
  }
  printf("\n\n");
*/

  for(i = 0; i < size; i++){
    if(floatcomp(a[i], b[i]) == 0){
      return 0;
    }
  }

  return 1;

}

void matrixeigen(int matrix[], float res[], int n){

  float vector[n];

  int i;

  //init vectors
  for(i = 0; i < n; i++){
    vector[i] = 1.0; //'let x be all 1 vector in appropriate dimmension'
    res[i] = 0.0;
  }

  while(1){

    matrvct(matrix, vector, res, n);

    float eigenValue = findmax(res, n);
    for(i = 0; i < n; i++){
      res[i] /= eigenValue;
    }

    if(isEqual(vector, res, n) == 1){
      break;
    }

    for(i = 0; i < n; i++){
      vector[i] = res[i];
    }

  }

}

void CSReigen(struct CSRgraph csr, int *res, int n){
/*
  float vector[n];

  int i;

  //init vectors
  for(i = 0; i < n; i++){
    vector[i] = 1.0; //'let x be all 1 vector in appropriate dimmension'
    res[i] = 0.0;
  }

  while(1){

    matrvct(matrix, vector, res, n);

    float eigenValue = findmax(res, n);
    for(i = 0; i < n; i++){
      res[i] /= eigenValue;
    }

    if(isEqual(vector, res, n) == 1){
      break;
    }

    for(i = 0; i < n; i++){
      vector[i] = res[i];
    }

  }
*/
}
