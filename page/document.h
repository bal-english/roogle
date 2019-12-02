#include <stdlib.h>
#include <stdio.h>

#ifndef DOCUMENT
#define DOCUMENT
struct Document {
  char* id;
  char* title;
  char* authors;
  int authornum;
  char* abstract;

  int matrixindex;
  float hubscore;
  float authscore;
  float pagerank;
};

void print_document(struct Document* d) {
  printf("%s\n%s\n%s\n%s\n", d->id, d->title, d->authors, d->abstract);
}
void create_new_document(struct Document* d,
                    char *_id,
                    char* _title,
                    char* _authors,
                    int _authornum,
                    char* _abstract) {
  d->id = _id;
  d->title = _title;
  d->authors = _authors;
  d->authornum = _authornum;
  d->abstract = _abstract;
}
void set_document_values(struct Document* d,
                    int matrixindex,
                    float hs,
                    float as,
                    float pr) {

  d->hubscore = hs;
  d->authscore = as;
  d->pagerank = pr;
}
void create_document(struct Document* d,
                    char *_id,
                    char* _title,
                    char* _authors,
                    int _authornum,
                    char* _abstract,

                    int matrixindex,
                    float hs,
                    float as,
                    float pr){
  create_new_document(d, _id, _title, _authors, _authornum, _abstract);
  set_document_values(d, matrixindex, hs, as, pr);
}
#endif
#ifndef DOCINDEX
#define DOCINDEX
typedef struct DocIndex {
  const char* doc_id;
  const int matrix_index;
} DocIndex;

void print_DocIndex(const DocIndex* di) {
  printf("%s: %d\n", di->doc_id, di->matrix_index);
}
void create_DocIndex(DocIndex* ptr, const char* id, const int index) {
  DocIndex di = {id, index};
  ptr = &di;
}
#endif
