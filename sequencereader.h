void capstring(char str[], int size){
  str[size-1] = '\0';
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

int endpaper(char line[]){
  if(strcmp(line, "+++++") == 0){
    return 1;
  }
  return 0;
}

int startcitations(char line[]){
  if(strcmp(line, "-----") == 0){
    return 1;
  }
  return 0;
}

void readfile(char *filename){
  int fd = open(filename, O_RDONLY);
  char linebuffer[200];
  int linesize;
  while(linesize = readline(linebuffer, fd) > 0){
    printf("%s\n", linebuffer);
  }
}
