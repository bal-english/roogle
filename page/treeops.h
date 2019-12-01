
/*

searching utils will return:
1 - search successful
0 - search unsuccessful

*/

int dictRecurseAppend(struct RBNode *node, char *val, int index){
  if(node == NIL){
    //printf("could not find word %s\n", val);
    return 0;
  }
  int compare = strcmp(node->data, val);
  if(compare == 0){
    //printf("found word %s in tree\n", node->data);

    appendtolist(node->list, index);
    printf("%s -> ", node->data);
    printlist(node->list);
    return 1;

  } else if(compare < 0){
    return dictRecurseAppend(node->left, val, index);
  } else {
    return dictRecurseAppend(node->right, val, index);
  }
}

int appendIndex(struct RBTree* t, char *val, int index){
  return dictRecurseAppend(t->root, val, index);
}

struct idList *dictRecurseGet(struct RBNode *node, char *val){
  if(node == NIL){
    return 0;
  }
  int compare = strcmp(node->data, val);
  if(compare == 0){
    return node->list;
  } else if(compare < 0){
    return dictRecurseGet(node->left, val);
  } else {
    return dictRecurseGet(node->right, val);
  }
}

struct idList *getIndexList(struct RBTree* t, char *val){
  return dictRecurseGet(t->root, val);
}

void preorder(struct RBNode* r){
  if(r == NIL) return;
  printf("%s\n", r->data);
  preorder(r->left);
  printf("\n--->\n");
  preorder(r->right);
}

/*

adding to trees

*/

//add index to words list of documents ids
//ex. document has certain word in its abstract, add its index
//to that words list of ids
//if we couldnt find that word, insert it
void addIdtoWord(struct RBTree* t, char *word, int index){

  int res = appendIndex(t, word, index);
  if(res == 0){
    //printf("inserting word %s into tree...\n", word);
    insert(t, word);
    addIdtoWord(t, word, index); //try it again, itll work this time
  }
}

int getWordIndexList(struct RBTree* t, char *word, int indexes[]){

  struct idList *res = getIndexList(t, word);
  if(res == NULL) return 0;
  return convertToArr(res, indexes);

}
