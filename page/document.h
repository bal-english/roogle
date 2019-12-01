
struct Document {
  char *id;
  char* title;
  char** authors;
  int authornum;
  char* abstract;

  int matrixindex;
  float hubscore;
  float authscore;
  float pagerank;
};

void create_document(struct Document* d,
                    char *_id,
                    char* _title,
                    char** _authors,
                    int _authornum,
                    char* _abstract,

                    int matrixindex,
                    float hs,
                    float as,
                    float pr){
  d->id = _id;
  d->title = _title;
  d->authors = _authors;
  d->authornum = _authornum;
  d->abstract = _abstract;

  d->hubscore = hs;
  d->authscore = as;
  d->pagerank = pr;
}
