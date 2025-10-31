#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"


tree_node *create_node(const char *text)
{
    tree_node *node = (tree_node *)malloc(sizeof(tree_node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    node->text = (char *)malloc(strlen(text) + 1);
    if (node->text == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(node);
        exit(1);
    }
    
    strcpy(node->text, text);
    node->yes = NULL;
    node->no = NULL;
    
    return node;
}

void free_tree(tree_node *root)
{
    if (root == NULL)
        return;
    
    free_tree(root->yes);
    free_tree(root->no);
    
    free(root->text);
    free(root);
}

int is_leaf(tree_node *node)
{
    return (node->yes == NULL && node->no == NULL);
}