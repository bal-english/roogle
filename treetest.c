#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "csr.h"
#include "eigen.h"
#include "dictlist.h"
#include "document.h"
//#include "rbtree.h"
#include "ditree.h"
#include "kwtree.h"
#include "treeops.h"
#include "sequencereader.h"

int main(int argc, char **argv){

  //char *str = "This is the zebra, each. word goes/ in individually, this is for how 0 as well if that makes a difference.";
  char *str = "This is the word goes/ in individually, yes/ you, or how difference 0 as well if that makes a big";
  char *str2 = "Now were at a second abstact, this one is a bit more sensible";
  char *str3 = "Specially/ we view vectors as column matrices, the matrix vector product is simply a special case of the matrix matrix product";
  char *str4 = "PageRank works by counting the number and quality of links to a page to determine a rough estimate of how important the website is. The underlying assumption is that more important websites are likely to receive more links from other websites";
  char *str5 = "Due to the huge number of items that are available or related to the query, there usually are several pages in response to a single search query as the search engine or the user's preferences restrict viewing to a subset of results per page";
  char *str6 = "Albania lies across the convergent boundary between the Eurasian Plate and the Adriatic Plate, part of the complex collision zone with the African Plate. The structure of the western part of Albania is dominated by active";

  struct KWTree tree;
  struct KWTree* kwt = &tree;
  create_KWTree(kwt, "test");
  //print_KWTree(kwt);

  insertAbstract(kwt, str, 0);
  insertAbstract(kwt, str2, 1);
  insertAbstract(kwt, str3, 2);
  insertAbstract(kwt, str4, 3);
  insertAbstract(kwt, str5, 4);
  insertAbstract(kwt, str6, 5);

  //print_KWTree(kwt);

  struct idList *res = (struct idList*)malloc(sizeof (struct idList));
  initlist(res);
  getKeywordDocs(kwt, "albania", res);
  //printlist(res);

  struct DITree doctree;
  struct DITree* dt = &doctree;

  DocIndex docind = {"psy/10000", 0};
  DocIndex *di = &docind;
  create_DITree(dt, di);

  DocIndex docind1 = {"cosc/43243", 2};
  DocIndex *di2 = &docind1;
  DITree_insert_di(dt, di2);

  char *psypaper = "psy/149341";
  int ind = 3;

  DocIndex docind2 = {psypaper, ind};
  DocIndex *di3 = &docind2;
  DITree_insert_di(dt, di3);

  //print_DITree(dt);


  int n = 5;
  int i;
  int matrix[n*n];

  initMatrix(matrix, n);

  int hub[n];
  int authority[n];

  hits(matrix, authority, hub, n);

  printMatrix(matrix, n);

  struct CSRgraph graph;

  matrixtocsr(matrix, n, &graph);

  //debugprint(graph);
  offsetprint(graph);

  int hub2[n];
  int auth2[n];

  //HITS testing

  sparsehit(graph, auth2, hub2, n);

  //pagerank testing

  float res1[n];
  float res2[n];

  matrixeigen(matrix, res1, n);
  CSReigen(graph, res2, n);


  printf("\n\n~~~read testing~~~\n\n");

  readfile("sample.txt");

  /*
  printf("\n...\n");
  struct KWTree tree;
  struct KWTree* kwt = &tree;
  create_KWTree(kwt, "This");
  print_KWTree(kwt);

  KWTree_insert_kw(kwt, "is");
  KWTree_insert_kw(kwt, "the");
  KWTree_insert_kw(kwt, "word");
  KWTree_insert_kw(kwt, "goes");
  KWTree_insert_kw(kwt, "in");
  KWTree_insert_kw(kwt, "individually");
  KWTree_insert_kw(kwt, "for");
  KWTree_insert_kw(kwt, "how");
  KWTree_insert_kw(kwt, "difference");
  KWTree_insert_kw(kwt, "0");
  KWTree_insert_kw(kwt, "as");

  print_KWTree(kwt);

  printf("inserted all words\n");
*/
/*
  int arr[50];
  int size = getWordIndexList(dt, "is", arr);

  printf("is -> ");
  for(i = 0; i < size; i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
*/

  return 0;

}
