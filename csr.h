
#include "matrix.h"

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

struct CSRgraph matrixtocsr(int *matrix, int n){

  struct CSRgraph graph;

  int dest_offsets[n];
  int source_indices[(n * n)]; //max edges is n*n
  int nv = n, ne = 0;

  int i, j;
  for(i = 0; i < n; i++){
    dest_offsets[i] = ne;
    for(j = 0; j < n; j++){

      int index = INDEX(n,i,j);
      if(matrix[index] != -1){
        source_indices[ne] = matrix[index];
        ne++;
      }
    }

  }

  return graph;

}
