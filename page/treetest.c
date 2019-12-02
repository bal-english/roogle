#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "csr.h"
#include "eigen.h"
#include "dictlist.h"
//#include "rbtree.h"
#include "treeops.h"
#include "kwtree.h"
int main(int argc, char **argv){


  // struct RBTree* dt = (struct RBTree*)malloc(sizeof (struct RBTree));
  // dt->root = NIL;

  //char *str = "This is the zebra, each. word goes/ in individually, this is for how 0 as well if that makes a difference.";
  char *str = "This is the word goes/ in individually, for how difference 0 as well if that makes a big";



  int wordsperabstract = 150;
  int maxwordsize = 25;

  int i;
  char **strarr = malloc(sizeof(char*) * wordsperabstract);
  for(i = 0; i < wordsperabstract; i++){
    strarr[i] = malloc(sizeof(char)*maxwordsize);
  }

  splitstr(str, strarr, " \0");
  int newsize = getstrarrsize(strarr);
  cleanstrings(strarr, ",./", newsize);


/*

  int n = 6;
  int matrix[n*n];

  initMatrix(matrix, n);

  int hub[n];
  int authority[n];

  hits(matrix, authority, hub, n);

  for(i = 0; i < n; i++){
    printf("%d ", authority[i]);
  }
  printf("\n");

  for(i = 0; i < n; i++){
    printf("%d ", hub[i]);
  }

  printMatrix(matrix, n);

  struct CSRgraph graph;

  matrixtocsr(matrix, n, &graph);

  debugprint(graph);
  offsetprint(graph);

*/



/*
  printf("words to add:\n");
  for(i = 0; i < newsize; i++){
    printf("%s\n", strarr[i]);
  }

  printf("\n...\n");
  for(i = 0; i < newsize; i++){
    printf("adding word %s\n", strarr[i]);
    insert(dt, strarr[i]);
    //addIdtoWord(dt, strarr[i], 0);
    print_tree(dt);
    printf("\n\n---------------\n\n");
  }
  printf("inserted all words\n");
  */

  printf("words to add:\n");
  for(i = 0; i < newsize; i++){
    printf("%s\n", strarr[i]);
  }
  printf("\n...\n");
  struct KWTree tree;
  struct KWTree* kwt = &tree;
  create_KWTree(kwt, strarr[0]);
  print_KWTree(kwt);
  for(i = 1; i < newsize; i++) {
    printf("adding word %s\n", strarr[i]);
    KWTree_insert_kw(kwt, strarr[i]);

    print_KWTree(kwt);
    printf("\n\n---------------\n\n");
  }
  printf("inserted all words\n");

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
