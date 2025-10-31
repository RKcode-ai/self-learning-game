#ifndef IO_HEADER
#define IO_HEADER

#include "tree.h"

tree_node *load_tree(const char *filename);
void save_tree(tree_node *root, const char *filename);

#endif 