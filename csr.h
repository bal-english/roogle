
#include "matrix.h"

//inspiration for Compressed Sparse Row encoding from
//NVIDIA CUDA nvGRAPH library
//https://docs.nvidia.com/cuda/nvgraph/index.html

//how it works is we essentially have two strided arrays
//one corresponds to the indices in the other
//e.g. - destination offsets

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
  for(i = 0; i < nv+1; i++){
    g->dest_offsets[i] = dest_offsets[i];
  }

  for(i = 0; i < ne+1; i++){
    g->source_indices[i] = source_indices[i];
  }

}

void freegraph(struct CSRgraph *g){
  free(g->dest_offsets);
  free(g->source_indices);
}

void debugprint(struct CSRgraph g){

  int i, j;
  for(i = 0; i < g.nvertices; i++){
    int lowerBound = g.dest_offsets[i];
    int upperBound = g.dest_offsets[i+1];
    for(j = lowerBound; j < upperBound; j++){
      printf("vertex %d --> %d\n", i, g.source_indices[j]);
    }
  }
}

void offsetprint(struct CSRgraph g){

  int i, j;
  for(i = 0; i < g.nvertices+1; i++){
    printf("%d, ", g.dest_offsets[i]);
  }
  printf("\n\n");
  for(i = 0; i < g.nedges+1; i++){
    printf("(%d, %d)\n", i, g.source_indices[i]);
  }
  printf("\n");
}

void statprint(struct CSRgraph g){

  printf("graph stats) v: %d e: %d\n", g.nvertices, g.nedges);

}


//convert an adjacency matrix to
//compressed sparse row

struct CSRgraph matrixtocsr(int matrix[], int n){

  struct CSRgraph graph;

  int dest_offsets[n+1];
  int source_indices[(n * n)+1]; //max edges is n*n
  int nv = n, ne = 0;

  int i, j;
  for(i = 0; i < n; i++){
    dest_offsets[i] = ne;
    for(j = 0; j < n; j++){

      int index = INDEX(n,i,j);
      if(matrix[index] != 0){
        source_indices[ne] = matrix[index];
        ne++;
      }
    }
  }

  ne--;

  dest_offsets[i] = ne;

  setgraph(&graph, dest_offsets, source_indices, nv, ne);

  return graph;

}
