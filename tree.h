#ifndef TREE_HEADER
#define TREE_HEADER

typedef struct tree_node{
    char *text;
    struct tree_node *yes;
    struct tree_node *no;
}tree_node;

tree_node *create_node(const char *text);
void free_tree(tree_node *root);
int is_leaf(tree_node *node);

#endif

