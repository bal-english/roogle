#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>
#include <math.h>

#include "csr.h" //matrix lib included in csr lib

//inspiration for Compressed Sparse Row encoding from
//NVIDIA CUDA nvGRAPH library
//https://docs.nvidia.com/cuda/nvgraph/index.html

int main(int argc, char **argv){

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank == 0){

    struct CSRgraph graph;

    int destination_offsets[] = {0, 1, 3, 4, 6, 8, 10};
    int source_indices[] = {2, 0, 2, 0, 4, 5, 2, 3, 3, 4};
    int nv = 7, nvz = 10;

    setgraph(&graph, destination_offsets, source_indices, nv, nvz);
    debugprint(graph);
    freegraph(&graph);

  }

  MPI_Finalize();

  return 0;
}
