

//we disregard my matrix multiplication calculator
//we only do matrix vector products here
//faster to just redo it
void matrixvectEigen(int matrix[], float vector[], float product[], int n){

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

void matrixvect(int matrix[], int vector[], int product[], int n){

  int i, j;

  for(i = 0; i < n; i++){

    product[i] = 0;

    for(j = 0; j < n; j++){
      int m = matrix[INDEX(n, i, j)], v = vector[j];
      //printf("Multiplying %.2f by %.2f\n", m, v);
      product[i] += (m * v);
    }
    //printf("%d sum: %.2f\n\n", i, product[i]);
  }

}

void CSRmatrvct(int matrix[], float vector[], float product[], int n){

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

    //take matrix-vector product
    //matrix * vector --> res
    matrixvectEigen(matrix, vector, res, n);

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

  //printouts
  printMatrix(matrix, n);
  for(i = 0; i < n; i++){
    printf("%.2f\n", res[i]);
  }

}

//sparse matrix multiplication
void sparsemult(struct CSRgraph csr, int vect[], int res[], int n){

  int i, j;
  for(i = 0; i < n; ++i){
    res[i] = 0;
    for(j = csr.dest_offsets[i]; j < csr.dest_offsets[i+1]; ++j){
      res[i] += 1 * vect[csr.source_indices[j]];
    }
  }
}

//sparse matrix mult with float arrs instead (for pagerank)
void sparsemult_f(struct CSRgraph csr, float vect[], float res[], int n){

  int i, j;
  for(i = 0; i < n; ++i){
    res[i] = 0;
    for(j = csr.dest_offsets[i]; j < csr.dest_offsets[i+1]; ++j){
      res[i] += 1 * vect[csr.source_indices[j]];
    }
  }
}


//do this part
//like this whole function
void sparsetranspose(struct CSRgraph *csr){

}

void sparsehit(struct CSRgraph csr, int auth[], int hub[], int n){

  //init vector of all 1's
  int vector[n];
  int i;

  for(i = 0; i < n; i++){
    vector[i] = 1;
  }

  sparsemult(csr, vector, hub, n); //get hub score

}


void CSReigen(struct CSRgraph csr, float res[], int n){

  float vector[n];
  int i;

  //init vectors
  for(i = 0; i < n; i++){
    vector[i] = 1.0; //'let x be all 1 vector in appropriate dimmension'
    res[i] = 0.0;
  }

  while(1){

    sparsemult_f(csr, vector, res, n);

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

void hits(int matrix[], int auth[], int hub[], int n){

  //init vector of all 1's
  int vector[n];
  int i;

  for(i = 0; i < n; i++){
    vector[i] = 1;
  }

  matrixvect(matrix, vector, hub, n);
  transpose(matrix, n);
  matrixvect(matrix, hub, auth, n);

  //transpose again to get original matrix
  transpose(matrix, n);

}
