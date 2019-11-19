#ifndef RBTREE
#define RBTREE

#include <stdbool.h>
#include <string.h>
#include <math.h>

#ifndef RBNODE
#define RBNODE

struct Node {
  bool is_red;
  char* data;
  struct Node* parent, * left, * right;
};

static struct Node nilvar = {false, "null", NULL, NULL, NULL};
static struct Node* const NIL = &nilvar;

void init_node(struct Node* n, bool iR) {
  n->is_red = iR;
  n->parent = NIL;
  n->left = NIL;
  n->right = NIL;
  n->data = ".";
}

void create_node(struct Node* n, char* str, bool iR) {
  init_node(n, iR);
  n->data = str;
}

void create_node_def(struct Node* n, char* str) {
  create_node(n, str, false);
}

int nodecmp(struct Node* n1, struct Node* n2) {
  return strcmp(n1->data, n2->data);
}

bool append_left(struct Node* p, struct Node* l) {
  bool noerr = true;
  if(p->left != NIL && p->left->parent != NIL) {
    //#warning Left child of parent was orphaned on left insertion
    noerr = false;
  } else if(l->parent != NIL && l->parent->left != NIL) {
    //#warning Parent of left node was left pointing to left node on left insertion
    noerr = false;
  }
  p->left = l;
  l->parent = p;
  return noerr;
}

bool append_right(struct Node* p, struct Node* r) {
  bool noerr = true;
  if(p->right != NIL && p->right->parent != NIL) {
    //#warning Right child of parent was orphaned on right insertion
    noerr = false;
  } else if(r->parent != NIL && r->parent->right != NIL) {
    //#warning Parent of right node was right pointing to right node on right insertion
    noerr = false;
  }
  p->right = r;
  r->parent = p;
  return noerr;
}

void print_spaces(int i) {
  for(int a = 0; a < i; a++) {
    printf("    ");
  }
}
void print_subtree_colors_recursive(struct Node* n, int level) {
  if(n == NIL)
    return;
  print_subtree_colors_recursive(n->right, level+1);
  print_spaces(level);
  if(n->is_red)
    printf("R");
  else
    printf("B");
  puts("");
  print_subtree_colors_recursive(n->left, level+1);

}
void print_subtree_colors(struct Node* n) {
  if(n == NIL) {
    puts("Empty Sub Tree.");
    return;
  }
  print_subtree_colors_recursive(n, 0);
}
#endif

struct RBTree {
  struct Node* root;
  int size, longest_word;
};

void print_tree(struct RBTree* tree) {
  if(tree->size < 1) {
    puts("Empty Tree.");
    return;
  }
  puts("Tree:");
  print_subtree_colors_recursive(tree->root, 0);
}
void print_tree_debug(struct RBTree* tree) {
  if(tree->root == NIL) {
    puts("Empty.");
  }
  printf("Tree | Size: %d, Longest Len: %d\n", tree->size, tree->longest_word);
  printf("Root: "); if(tree->root->is_red) printf("R"); else printf("B");
  printf("-%s\n", tree->root->data);
  printf("\tLC: ");
  if(tree->root->left != NIL) {
    if(tree->root->left->is_red)
      printf("R");
    else
      printf("B");
    printf("-%s\n", tree->root->left->data);
  } else {
    puts("E");
  }

  printf("\t\tLC: ");
  if(tree->root->left->left != NIL) {
    if(tree->root->left->left->is_red)
      printf("R");
    else
      printf("B");
    printf("-%s\n", tree->root->left->left->data);
  } else {
    puts("E");
  }

  printf("\t\tRC: ");
  if(tree->root->left->right != NIL) {
    if(tree->root->left->right->is_red)
      printf("R");
    else
      printf("B");
    printf("-%s\n", tree->root->left->right->data);
  } else {
    puts("E");
  }

  printf("\tRC: ");
  if(tree->root->right != NIL) {
    if(tree->root->right->is_red) printf("R"); else printf("B");
    printf("-%s\n", tree->root->right->data);
  } else
    puts("E");
}
void init_tree(struct RBTree* tree) {
  tree->root = malloc(sizeof(struct Node));
  tree->size = 0;
  tree->longest_word = -1;
}
void create_tree(struct RBTree* tree, char* str) {
  init_tree(tree);
  create_node_def(tree->root, str);
  tree->size++;
  tree->longest_word = strlen(str);
}

/*void rotatel(struct RBTree* tree, struct Node* node) {
  struct Node* nr = node->right;
  node->right = node->right->left;
  if(node->right != NIL) {
    node->right->parent = node;
  }
  nr->parent = node->parent;
  if(node->parent == NIL)
    tree->root = nr;
  else if(node == node->parent->left)
    node->parent->left = nr;
  else
    node->parent->right = nr;

  nr->left = node;
  node->parent = nr;
}
void rotater(struct RBTree* tree, struct Node* node) {
  struct Node* nl = node->left;
  if(node->left != NIL)
    node->left->parent = node;
  nl->parent = node->parent;
  if(node->parent == NIL)
    tree->root = nl;
  else if(node == node->parent->right)
    node->parent->right = nl;
  else
    node->parent->left = nl;

  nl->right = node;
  node->parent = nl;
}*/
void newrotater(struct RBTree* tree, struct Node* n) {
  struct Node* nl = n->left;

  nl->parent = n->parent;
  if(n->parent == NIL)
    tree->root = nl;
  else if(n == n->parent->right)
    n->parent->right = nl;
  else
    n->parent->left = nl;

  struct Node* migrant = nl->right;

  n->left = migrant;
  migrant->parent = n;
  nl->right = n;

}
void newrotatel(struct RBTree* tree, struct Node* n) {
  struct Node* nr = n->right;

  nr->parent = n->parent;
  if(n->parent == NIL)
    tree->root = nr;
  else if(n == n->parent->left)
    n->parent->left = nr;
  else
    n->parent->right = nr;

  struct Node* migrant = nr->left;

  n->right = migrant;
  migrant->parent = n;
  nr->left = n;
}
void color_fix(struct RBTree* tree, struct Node* node) {
  struct Node* n = node;
  while(n->parent->is_red) {
    if(n->parent == n->parent->parent->left) {
      struct Node* uncle = n->parent->parent->right;
      if(uncle->is_red) {
        n->parent->is_red = false;
        uncle->is_red = false;
        n->parent->parent->is_red = true;
        n = n->parent->parent;
      } else {
        if(n == n->parent->right) {
          n = n->parent;
          newrotatel(tree, n);
        }
        n->parent->is_red = false;
        n->parent->parent->is_red = true;
        newrotater(tree, n->parent->parent);
      }
    } else {
      struct Node* uncle = n->parent->parent->left;
      if(uncle->is_red) {
        n->parent->is_red = false;
        uncle->is_red = false;
        n->parent->parent->is_red = true;
        n = n->parent->parent;
      } else {
        if(node == node->parent->left) {
          n = n->parent;
          newrotater(tree, n);
        }
        n->parent->is_red = false;
        n->parent->parent->is_red = true;
        newrotatel(tree, n->parent->parent);
      }
    }
  }
  tree->root->is_red = false;
}
void insert(struct RBTree* tree, char* str) {
  if(tree->root == NIL) {
    create_tree(tree, str);
    return;
  }
  struct Node* newptr = malloc(sizeof(struct Node));
  create_node_def(newptr, str);
  struct Node* current = tree->root;

  bool loop = current != NIL;
  while(loop) {
    if(nodecmp(current, newptr) < 0) {
      if(current->left == NIL) {
        append_left(current, newptr);
        loop = false;
      } else
        current = current->left;
    } else {
      if(current->right == NIL) {
        append_right(current, newptr);
        loop = false;
      } else
        current = current->right;
    }
    if(loop)
      loop = current != NIL;
  }
  tree->size++;
  int len = strlen(newptr->data);
  if(len > tree->longest_word)
    tree->longest_word = len;
  newptr->is_red = true;
  color_fix(tree, newptr);
}


#endif
