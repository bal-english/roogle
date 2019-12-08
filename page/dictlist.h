
struct idNode {
  int index;
  struct idNode *next;
};

struct idList {
  struct idNode *first;
  struct idNode *last;
  int size;
};

void initlist(struct idList *list){
  //list = (struct idList*)malloc(sizeof (struct idList));
  list->first = NULL;
  list->last = NULL;
  list->size = 0;
}

void appendtolist(struct idList *list, int index){
  //create first node in list
  if(list == NULL){
    initlist(list);
  }
  if(list->first == NULL){
    list->first = (struct idNode*)malloc(sizeof (struct idNode));
    list->first->index = index;
    list->last = list->first;
    list->size++;
    return;
  }
  //append to last node
  list->last->next = (struct idNode*)malloc(sizeof (struct idNode));
  list->last->next->index = index;
  list->last = list->last->next;
  list->size++;
}

void printlist(struct idList *list){
  struct idNode *curr = list->first;
  while(curr != NULL){
    printf("%d, ", curr->index);
    curr = curr->next;
  }
  printf("\n");
}

int convertToArr(struct idList *list, int arr[]){

  int index = 0;
  struct idNode *curr = list->first;

  while(curr != NULL){
    arr[index] = curr->index;
    index++;
    curr = curr->next;
  }
  return index;
}

void freelist(struct idList *list){
  struct idNode *curr = list->first;
  while(curr != NULL){
    struct idNode *temp = curr;
    curr = curr->next;
    free(temp);
  }
  free(list);
}
