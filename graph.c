#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>
#include <math.h>

#include "csr.h"

int main(int argc, char **argv){

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank == 0){

    int nsize = 16;

    int matr[nsize*nsize];

    initMatrix(matr, nsize);
    printMatrix(matr, nsize);

    struct CSRgraph graph1 = matrixtocsr(matr, nsize);

    statprint(graph1);
    //offsetprint(graph1);
    //debugprint(graph1);

    freegraph(&graph1);

    /*
    struct CSRgraph graph;

    int destination_offsets[] = {0, 1, 3, 4, 6, 8, 10};
    int source_indices[] = {2, 0, 2, 0, 4, 5, 2, 3, 3, 4};
    int nv = 6, nvz = 9;
    setgraph(&graph, destination_offsets, source_indices, nv, nvz);
    debugprint(graph);
    freegraph(&graph);
    */

  }

  MPI_Finalize();

  return 0;
}
