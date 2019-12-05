struct Citenode {
  int index;
  Citenode *next;
};

void buildCiteList(struct DITree* dt char *origin, char **citations, int nc, Citenode* citearray[]){

  int originIndex = dt.get(origin); //////////////////////////
  Citenode *start = (struct Citenode*)malloc(sizeof (struct Citenode));

  struct Citenode *curr = start;

  int i;
  for(i = 0; i < nc; i++){
    int currindex = dt.get(citations[i]); //////////////////////////
    curr->next = (struct Citenode*)malloc(sizeof (struct Citenode)); //make a new one after it
    curr = curr->next; //go there, and set the index
    curr->index = currindex;
  }

  citearray[originIndex] = start->next;

  free(start); //dont need start anymore, that was just a temp incase we didnt have a linked list lol

}

void buildCSRfromCitearr(struct CSRgraph *csr, Citenode *citearray, int papercount){

  //lets just make some buffers now
  //we'll resize later for efficiency
  //or we might not we'll see what happens

  int buffersize = 10000000;
  int offsets[buffersize];
  int sources[buffersize];

  offsets[0] = 0; //init first offset
  int currsource = 0;

  int i;
  for(i = 0; i < papercount; i++){

    //iterate through list for each citation list
    Citenode *curr = citearray[i];
    while(curr != NULL){

      sources[currsource] = curr->index;
      currsource++;

      //move to next, delete old
      Citenode *temp = curr;
      curr = curr->next;
      free(temp);
    }

    offsets[i+1] = currsource;
  }

  //finally, set the graph with all our temp data
  setgraph(csr, offsets, sources, papercount, currsource);

}
