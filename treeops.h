#include "rbtree.h"
/*

searching utils will return:
1 - search successful
0 - search unsuccessful

*/



int dictRecurseAppend(struct RBNode *node, char *val, int index){
  if(node == NIL){
    printf("could not find word %s\n", val);
    return 0;
  }
  int compare = strcmp(node->data, val);
  if(compare == 0){
    printf("found word %s in tree\n", node->data);

    appendtolist(node->list, index);
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



int addIdtoDocRecurse(struct RBNode *node, char *id, int index){
  if(node == NIL){
    //printf("could not find word %s\n", val);
    return 0;
  }
  int compare = strcmp(node->data, id);
  if(compare == 0){
    node->index = index;
    printf("node found: %s : %d\n", node->data, node->index);
    return 1;
  } else if(compare < 0){
    return addIdtoDocRecurse(node->left, id, index);
  } else {
    return addIdtoDocRecurse(node->right, id, index);
  }
}

int addIdToDoc(struct RBTree* t, char *id, int index){
  insert(t, id);
  return addIdtoDocRecurse(t->root, id, index);
}


int docGetIndexRecurse(struct RBNode *node, char *id){
  if(node == NIL){
    return -1;
  }
  int compare = strcmp(node->data, id);
  if(compare == 0){
    return node->index;
  } else if(compare < 0){
    return docGetIndexRecurse(node->left, id);
  } else {
    return docGetIndexRecurse(node->right, id);
  }
}

int getDocIndex(struct RBTree* t, char *id){
  return docGetIndexRecurse(t->root, id);
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
    printf("inserting word %s into tree...\n", word);
    insert(t, word);
    printf("trying again...\n");
    addIdtoWord(t, word, index); //try it again, itll work this time
  }
}

int getWordIndexList(struct RBTree* t, char *word, int indexes[]){

  struct idList *res = getIndexList(t, word);
  if(res == NULL) return 0;
  return convertToArr(res, indexes);

}


int comparetodelims(char curr, char *delims){
  int i, j;
  for(i = 0; i < strlen(delims); i++){
    if(delims[i] == curr){
      return 1;
    }
  }
  return 0;
}

void splitstr(char *str, char **strarr, char *delims){
  int i, j = 0;
  int curr = 0;
  for(i = 0; i < strlen(str); i++){
    if(comparetodelims(str[i], delims)){
      strarr[curr][j] = '\0';
      curr++;
      j = 0;
    } else {
      strarr[curr][j] = str[i];
      j++;
    }
  }
}

//convert all chars in string to lower case
void lowerall(char *str){
  int i;
  for(i = 0; i < strlen(str); i++){
    str[i] = tolower(str[i]);
  }
}

void cleanstrings(char **strarr, char *badchars, int strs){
  int i, j;
  for(i = 0; i < strs; i++){
    lowerall(strarr[i]); //first put entire string to lowercase
    for(j = 0; j < strlen(strarr[i]); j++){
      //printf("%c ", strarr[i][j]);
      if(comparetodelims(strarr[i][j], badchars)){
        if(j == strlen(strarr[i])-1){
          strarr[i][j] = '\0';
        }
      }
      continue;
    }
  }
}

int getstrarrsize(char **strarr){
  char *curr;
  int index = 0;
  while(1){
    curr = strarr[index];
    if(strlen(curr) == 0){
      break;
    }
    index++;
  }
  return index;
}

//insert entire abstract into tree
void insertAbstract(struct KWTree *tree, char *abstract, int index){

  //just some standard stuff, will be dealloced after this
  int wordsperabstract = 150;
  int maxwordsize = 25;

  int i;
  char **strarr = malloc(sizeof(char*) * wordsperabstract);
  for(i = 0; i < wordsperabstract; i++){
    strarr[i] = malloc(sizeof(char)*maxwordsize);
  }

  splitstr(abstract, strarr, " \0");
  int newsize = getstrarrsize(strarr);
  //get rid of any special chars
  cleanstrings(strarr, ",./", newsize);

  for(i = 0; i < newsize; i++){
    //printf("adding word %s\n", strarr[i]);
    KWTree_insert(tree, strarr[i], index);
  }
  //printf("inserted all words\n");

}
/*
void getKeywordDocs(struct KWTree *tree, char *keyword, int docIndices[]){

  struct idList *res = getIndexList(tree, keyword);
  if(res == NULL) return 0;
  return convertToArr(res, indexes);

}
*/

void insertDocumentIndex(struct DITree *tree, char *id, int index){
  DocIndex docind = {id, index};
  DocIndex *di = &docind;
  DITree_insert_di(tree, di);
}
