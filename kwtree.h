#ifndef KWTREE
#define KWTREE

#include <stdbool.h>
#include <string.h>
#include "debug.h"
#include "dictlist.h"
#ifndef KWNODE
#define KWNODE

struct KWNode {
  bool is_red;
  char* data; //id (doc tree -> document id ... dicitonary tree -> word)

  //hold list of indexes in arr of docs
  struct idList *list;

  struct KWNode* parent, *left, *right;

};

static struct KWNode kwnilvar = {false, NULL, NULL, NULL, NULL, NULL};
static struct KWNode* const KWNIL = &kwnilvar;

void init_KWNode(struct KWNode* n, bool iR) {
  n->is_red = iR;
  n->parent = KWNIL;
  n->left = KWNIL;
  n->right = KWNIL;
  n->data = ".";
  initlist(n->list);
}

void create_KWNode(struct KWNode* n, char* str, bool iR) {
  init_KWNode(n, iR);
  n->data = str;
}

void create_KWNode_def(struct KWNode* n, char* str) {
  create_KWNode(n, str, false);
}

int KWNodecmp(struct KWNode* n1, struct KWNode* n2) {
  return strcmp(n1->data, n2->data);
}

bool KWNode_append_left(struct KWNode* p, struct KWNode* l) {
  bool noerr = true;
  if(p->left != KWNIL && p->left->parent != KWNIL) {
    //#warning Left child of parent was orphaned on left insertion
    noerr = false;
  } else if(l->parent != KWNIL && l->parent->left != KWNIL) {
    //#warning Parent of left KWNode was left pointing to left KWNode on left insertion
    noerr = false;
  }
  p->left = l;
  l->parent = p;
  return noerr;
}

bool KWNode_append_right(struct KWNode* p, struct KWNode* r) {
  bool noerr = true;
  if(p->right != KWNIL && p->right->parent != KWNIL) {
    //#warning Right child of parent was orphaned on right insertion
    noerr = false;
  } else if(r->parent != KWNIL && r->parent->right != KWNIL) {
    //#warning Parent of right KWNode was right pointing to right KWNode on right insertion
    noerr = false;
  }
  p->right = r;
  r->parent = p;
  return noerr;
}

void KW_print_spaces(int i) {
  for(int a = 0; a < i; a++) {
    printf("    ");
  }
}
void print_subKWTree_colors_recursive(struct KWNode* n, int level) {
  if(n == KWNIL)
    return;
  print_subKWTree_colors_recursive(n->right, level+1);
  KW_print_spaces(level);
  if(n->is_red)
    //printf("R");
    printf("R:%s", n->data);
  else
    printf("B:%s", n->data);
    //printf("B");
  puts("");
  print_subKWTree_colors_recursive(n->left, level+1);

}
void print_subKWTree_colors(struct KWNode* n) {
  if(n == KWNIL) {
    puts("Empty Sub KWTree.");
    return;
  }
  print_subKWTree_colors_recursive(n, 0);
}
#endif

struct KWTree {
  struct KWNode* root;
  int size;
};

void print_KWTree(struct KWTree* tree) {
  if(tree->size < 1) {
    puts("Empty KWTree.");
    return;
  }
  puts("KWTree:");
  print_subKWTree_colors_recursive(tree->root, 0);
  puts("");
}
void print_KWTree_debug(struct KWTree* tree) {
  if(tree->root == KWNIL) {
    puts("Empty.");
  }
  // printf("KWTree | Size: %d, Longest Len: %d\n", tree->size, tree->longest_word);
  printf("Root: "); if(tree->root->is_red) printf("R"); else printf("B");
  printf("-%s\n", tree->root->data);
  printf("\tLC: ");
  if(tree->root->left != KWNIL) {
    if(tree->root->left->is_red)
      printf("R");
    else
      printf("B");
    printf("-%s\n", tree->root->left->data);
  } else {
    puts("E");
  }

  printf("\t\tLC: ");
  if(tree->root->left->left != KWNIL) {
    if(tree->root->left->left->is_red)
      printf("R");
    else
      printf("B");
    printf("-%s\n", tree->root->left->left->data);
  } else {
    puts("E");
  }

  printf("\t\tRC: ");
  if(tree->root->left->right != KWNIL) {
    if(tree->root->left->right->is_red)
      printf("R");
    else
      printf("B");
    printf("-%s\n", tree->root->left->right->data);
  } else {
    puts("E");
  }

  printf("\tRC: ");
  if(tree->root->right != KWNIL) {
    if(tree->root->right->is_red) printf("R"); else printf("B");
    printf("-%s\n", tree->root->right->data);
  } else
    puts("E");
}
void init_KWTree(struct KWTree* tree) {
  tree->root = malloc(sizeof(struct KWNode));
  tree->size = 0;
}
void create_KWTree(struct KWTree* tree, char* str) {
  init_KWTree(tree);
  create_KWNode_def(tree->root, str);
  tree->size++;
}

void KWTree_rotater(struct KWTree* tree, struct KWNode* n) {
  struct KWNode* nl = n->left;

  nl->parent = n->parent;
  if(n->parent == KWNIL)
    tree->root = nl;
  else if(n == n->parent->right)
    n->parent->right = nl;
  else
    n->parent->left = nl;

  struct KWNode* migrant = nl->right;
  n->left = migrant;
  if(migrant != KWNIL) {
    migrant->parent = n;
  }
  nl->right = n;
  n->parent = nl;

}
void KWTree_rotatel(struct KWTree* tree, struct KWNode* n) {
  struct KWNode* nr = n->right;

  nr->parent = n->parent;
  if(n->parent == KWNIL)
    tree->root = nr;
  else if(n == n->parent->left)
    n->parent->left = nr;
  else
    n->parent->right = nr;

  struct KWNode* migrant = nr->left;
  //printf("%d\n", (bool)(migrant == KWNIL));
  n->right = migrant;
  //printf("node7: %s %s\n", migrant->data, n->right->data);
  if(migrant != KWNIL) {
    migrant->parent = n;
  }
  nr->left = n;
  n->parent = nr;
}
void KWTree_color_fix(struct KWTree* tree, struct KWNode* node) {
  struct KWNode* n = node;
  // puts("++++++++++++");
  // printf("node: %s\n", node->data);
  // printf("node parent: %s\n", node->parent->data);
  // printf("node parent parent: %s\n", node->parent->parent->data);
  // //printf("node parent parent left: %s\n", node->parent->parent->left->data);
  // print_KWTree(tree);
  // puts("------------");
  while(n->parent->is_red) {
    if(n->parent == n->parent->parent->left) {
      struct KWNode* uncle = n->parent->parent->right;
      if(uncle->is_red) {
        n->parent->is_red = false;
        uncle->is_red = false;
        n->parent->parent->is_red = true;
        n = n->parent->parent;
      } else {
        if(n == n->parent->right) {
          n = n->parent;
          KWTree_rotatel(tree, n);
        }
        n->parent->is_red = false;
        n->parent->parent->is_red = true;
        KWTree_rotater(tree, n->parent->parent);
      }
    } else {
      struct KWNode* uncle = n->parent->parent->left;
      if(uncle->is_red) {
        n->parent->is_red = false;
        uncle->is_red = false;
        n->parent->parent->is_red = true;
        n = n->parent->parent;
      } else {
        if(node == node->parent->left) {
          n = n->parent;
          KWTree_rotater(tree, n);
        }
        // puts("t1:");
        // print_KWTree(tree);
        n->parent->is_red = false;
        n->parent->parent->is_red = true;
        KWTree_rotatel(tree, n->parent->parent);
        // puts("t2:");
        // print_KWTree(tree);
        // printf("node: %s\n", n->data);
        // printf("node parent: %s\n", n->parent->data);
        // printf("node parent left: %s\n", n->parent->left->data);
        // printf("node parent left parent: %s\n", n->parent->left->parent->data);
      }
    }
  }
  tree->root->is_red = false;
}
struct KWNode* KWTree_insert_kw(struct KWTree* tree, char* str) {
  if(tree->root == KWNIL) {
    create_KWTree(tree, str);
    return tree->root;
  }
  struct KWNode* newptr = malloc(sizeof(struct KWNode));
  create_KWNode_def(newptr, str);
  struct KWNode* current = tree->root;

  bool loop = current != KWNIL;
  while(loop) {
    int cmp = KWNodecmp(newptr, current);
    if(cmp < 0) {
      if(current->left == KWNIL) {
        KWNode_append_left(current, newptr);
        loop = false;
      } else
        current = current->left;
    } else if(cmp > 0) {
      if(current->right == KWNIL) {
        KWNode_append_right(current, newptr);
        loop = false;
      } else
        current = current->right;
    } else {
      if(debug)
        printf("WARN: KWTree Insertion Failed, \"%s\" already exists.\n", str);
      free(newptr);
      return current;
    }
    if(loop)
      loop = current != KWNIL;
  }
  tree->size++;
  newptr->is_red = true;
  KWTree_color_fix(tree, newptr);
  return newptr;
}
struct KWNode* KWTree_insert(struct KWTree* tree, char* keyword, int index) {
  struct KWNode* kw_ptr = KWTree_insert_kw(tree, keyword);
  appendtolist(kw_ptr->list, index);
  return kw_ptr;
}

#endif
