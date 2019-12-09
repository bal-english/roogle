#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <mpi.h>

#include "csr.h"
#include "graph.h"
#include "dictlist.h"
#include "document.h"
#include "ditree.h"
#include "kwtree.h"
#include "citehandler.h"

/*

some stats we calc'd

size of full list of documents: 87*size mb
size of matrix encoding (ints 9.5tb) (bits 211gb)
size of CSR encoding:
  offsets (vertices) list: 6.4mb
  sources (edges) lists: ~300mb

*/

int main(int argc, char **argv){

  int wsize, rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &wsize);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if(rank == 0){

    //define graph
    struct CSRgraph graph;
    struct CSRgraph *csr = &graph;

    //create example tree
    struct DITree doctree;
    struct DITree* dt = &doctree;

    DocIndex docind = {"psy/10000", -5};
    DocIndex *di = &docind;
    create_DITree(dt, di);

    buildCSRfromCiteFile(csr, dt, "testing.txt"); //<-- pass CSRgraph, DItree, and name of citations file

    statprint(*csr); //<-- prints graph stats, optional

    //calc hub, auth, and pagerank

    int hub[csr->nvertices], auth[csr->nvertices];
    float pagerank[csr->nvertices];
    
    sparsehub(*csr, hub, csr->nvertices);
    sparseauth(*csr, auth, hub, csr->nvertices);
    sparsepagerank(*csr, pagerank);

  }

  MPI_Finalize();

  return 0;

}
