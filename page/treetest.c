#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "csr.h"
#include "eigen.h"
#include "document.h"
#include "dictlist.h"
#include "rbtree.h"
#include "treeops.h"

int main(int argc, char **argv){

/*
  char *words[6];

  words[0] = "a";
  words[1] = "b";
  words[2] = "c";

  struct RBTree* dictionaryTree = (struct RBTree*)malloc(sizeof (struct RBTree));
  dictionaryTree->root = NIL;

  int i;
  for(i = 0; i < 3; i++){
    printf("%s\n", words[i]);
    insert(dictionaryTree, words[i]);
  }

  print_tree(dictionaryTree);

  printf("\n~\n");
  preorder(dictionaryTree->root);
  printf("\n~\n");
*/

/*
  struct idList *l = (struct idList*)malloc(sizeof (struct idList));
  l->first = NULL;

  appendtolist(l, 1);
  appendtolist(l, 2);
  appendtolist(l, 3);
  appendtolist(l, 4);

  printlist(l);
  freelist(l);
*/



  struct RBTree* dt = (struct RBTree*)malloc(sizeof (struct RBTree));
  dt->root = NIL;

  addIdtoWord(dt, "test", 0);
  addIdtoWord(dt, "labas", 1);
  addIdtoWord(dt, "hello", 2);
  addIdtoWord(dt, "test", 3);
  addIdtoWord(dt, "ahoy", 4);
  addIdtoWord(dt, "hello", 5);
  addIdtoWord(dt, "ahoy", 5);
  addIdtoWord(dt, "labas", 5);
  addIdtoWord(dt, "labas", 6);

  int arr[50];
  int size = getWordIndexList(dt, "hello", arr);

  int i;
  printf("hello -> ");
  for(i = 0; i < size; i++){
    printf("%d ", arr[i]);
  }

  //print_tree(dt);

  return 0;

}
