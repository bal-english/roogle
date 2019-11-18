#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <mpi.h>
#include <math.h>

#include "matrix.h"

//inspiration for Compressed Sparse Row encoding from
//NVIDIA CUDA nvGRAPH library
//https://docs.nvidia.com/cuda/nvgraph/index.html

struct CSRgraph {
  int *dest_offsets;
  int *source_indices;
  int nvertices;
  int nedges;
};

void setgraph(struct CSRgraph *g,
              int dest_offsets[],
              int source_indices[],
              int nv,
              int ne){

  g->nvertices = nv;
  g->nedges = ne;
  g->dest_offsets = malloc(g->nvertices*sizeof(int));
  g->source_indices = malloc(g->nedges*sizeof(int));

  int i;
  for(i = 0; i < nv; i++){
    g->dest_offsets[i] = dest_offsets[i];
  }

  for(i = 0; i < ne; i++){
    g->source_indices[i] = source_indices[i];
  }

}

void freegraph(struct CSRgraph *g){

  free(g->dest_offsets);
  free(g->source_indices);

}

void debugprint(struct CSRgraph g){

  int i, j;
  for(i = 0; i < g.nvertices-1; i++){
    int lowerBound = g.dest_offsets[i];
    int upperBound = g.dest_offsets[i+1];
    for(j = lowerBound; j < upperBound; j++){
      printf("vertex %d --> %d\n", i, g.source_indices[j]);
    }
  }
}

struct CSRgraph matrixcsr(int *matrix){
  struct CSRgraph graph;

}

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
