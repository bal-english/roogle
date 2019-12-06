struct CiteIDholder {
  char *cite;
  struct CiteIDholder *next;
};

struct Citenode {
  int index;
  struct Citenode *next;
};


//from an array of citations (paper IDs)
//build a linked list of paper indices
void buildCiteList(struct DITree* dt, char *origin, char **citations, int nc, struct Citenode* citearray[]){

  int originIndex = 0;//dt.get(origin);
  struct Citenode *start = (struct Citenode*)malloc(sizeof (struct Citenode));
  struct Citenode *curr = start;

  int i;

  //nc=number of citations (how many char*s in citations)
  for(i = 0; i < nc; i++){

    int currindex = 0;//dt.get(citations[i]);
    curr->next = (struct Citenode*)malloc(sizeof (struct Citenode)); //make a new one after it
    curr = curr->next;
    curr->index = currindex;
  }

  //dont store the origin index in the list
  //we cant get that throught the index of the array
  //instead, store the starting cite node
  citearray[originIndex] = start->next;

  free(start); //dont need start anymore, that was just a temp incase we didnt have a linked list lol

}

void buildCSRfromCitearr(struct CSRgraph *csr, struct Citenode *citearray[], int papercount){

  //lets just make some buffers now
  //we'll resize later for efficiency
  //or we might not (budget cuts)

  int buffersize = 10000000;
  int offsets[buffersize];
  int sources[buffersize];

  offsets[0] = 0; //init first offset
  int currsource = 0;

  int i;
  for(i = 0; i < papercount; i++){

    //iterate through list for each citation list
    struct Citenode *curr = citearray[i];
    while(curr != NULL){

      //set current source to be index of citation
      sources[currsource] = curr->index;
      currsource++;

      //move to next, delete old
      struct Citenode *temp = curr;
      curr = curr->next;
      free(temp);
    }

    offsets[i+1] = currsource;
  }

  //finally, set the graph with all our temp data
  setgraph(csr, offsets, sources, papercount, currsource);

}
