void capstring(char str[], int size){
  str[size] = '\0';
}

int readline(char str[], int fd){
  char buffer[1];
  int nread, curr = 0;
  while ((nread = read(fd, buffer, 1) > 0)){
    if(buffer[0] == '\n'){
      capstring(str, curr);
      return curr;
    }
    str[curr] = buffer[0];
    curr++;
  }
  return -1;
}

void printcitelist(char *list[], int numcites){
  int i;
  for(i = 0; i < numcites; i++){
    
    if(i == 0){
       printf("origin: %s\n", list[i]);
       continue;
     }

    printf("%s\n", list[i]);
  }
  printf("\n~~~\n");
}

//convert linked list of cites to an array of cite strings
//NOTE: this is invidividual for each paper
//ran after each individual linked list is created
void formatCites(char *cites[], int numcites){

  int i;

  //copying everything from cites[] to list[]
  //except first, thats the origin paper
  char *origin = malloc(sizeof(char*) * strlen(cites[0]));
  char *list[numcites-1];

  printcitelist(cites, numcites);

  for(i = 1; i < numcites; i++){

    list[i] = malloc(sizeof(char *) * strlen(cites[i]));
    strcpy(list[i], cites[i]);

  }

  //also deallocate cites[] while were here
  for(i = 0; i < numcites; i++){
    free(cites[i]);
  }

}

int paperdelim(char *line){
  if(strcmp(line, "+++++") == 0){
    return 1;
  }
  return 0;
}

int citedelim(char *line){
  if(strcmp(line, "-----") == 0){
    return 1;
  }
  return 0;
}

//put cites into individual cite arrays
//numcites is count of all citations in file
void processCites(char **allcontent, int numcites){

  int i;
  int currcitecount = 0;
  int maxcitesperpaper = 200;

  char *curr[maxcitesperpaper];

  for(i = 0; i < numcites; i++){

    //when we hit a ++++++
    //get the linked list into the array
    //reset it (we have to reallocate cause formatCites deletes it after its read)
    if(paperdelim(allcontent[i])){
      formatCites(curr, currcitecount);
      currcitecount = 0;
      continue;
    }

    if(citedelim(allcontent[i])){
      continue; //just skip the ------ lines
    }

    //copy from full list to array
    curr[currcitecount] = malloc(sizeof(char*) * strlen(allcontent[i]));
    strcpy(curr[currcitecount], allcontent[i]);
    currcitecount++;

  }

  //the last one will never get hit since there is no +++++ to end file
  //just do it manually here
  formatCites(curr, currcitecount);

  //finally, deallocate citations in full list
  for(i = 0; i < numcites; i++){
    free(allcontent[i]);
  }
  free(allcontent);

}

void readfile(char *filename){
  int fd = open(filename, O_RDONLY);
  char linebuffer[200];
  int linesize;

  //store all cites in list of char*s
  int linecount = 1000;
  char **allcites = malloc(sizeof(char*) * linecount);
  int currcite = 0;

  while(linesize = readline(linebuffer, fd) > 0){

    allcites[currcite] = malloc(sizeof(char) * strlen(linebuffer));
    strcpy(allcites[currcite], linebuffer);
    currcite++;

  }
  processCites(allcites, currcite);
}
