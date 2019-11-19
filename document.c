#ifndef DOCUMENT
#define DOCUMENT

typedef struct Document {
  float id;
  char* title;
  char** authors;
  int authornum;
  char* abstract;
} Doc;

void create_document(Doc* d, float _id, char* _title, char** _authors, int _authornum, char* _abstract) {
  d->id = _id;
  d->title = _title;
  d->authors = _authors;
  d->authornum = _authornum;
  d->abstract = _abstract;
}

#endif
