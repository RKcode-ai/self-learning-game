#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
#include "tree.h"


void save_tree_helper(tree_node *node, FILE *file)
{
    if (node == NULL) {
        fprintf(file, "#\n");  
        return;
    }
    
    if (is_leaf(node))
        fprintf(file, "G\n");
    else
        fprintf(file, "Q\n");
    
    fprintf(file, "%s\n", node->text);
    
    if (!is_leaf(node)) {
        save_tree_helper(node->yes, file);
        save_tree_helper(node->no, file);
    }
}

void save_tree(tree_node *root, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Could not open file for writing: %s\n", filename);
        return;
    }
    
    save_tree_helper(root, file);
    fclose(file);
    printf("Tree saved to %s\n", filename);
}

tree_node *load_tree_helper(FILE *file)
{
    char type[10];
    char buffer[256];
    if (fgets(type, sizeof(type), file) == NULL)
        return NULL;
    type[strcspn(type, "\n")] = 0;
    if (strcmp(type, "#") == 0)
        return NULL;
    if (fgets(buffer, sizeof(buffer), file) == NULL)
        return NULL;
    buffer[strcspn(buffer, "\n")] = 0;
    tree_node *node = create_node(buffer);
    if (strcmp(type, "Q") == 0) {
        node->yes = load_tree_helper(file);
        node->no = load_tree_helper(file);
    }
    
    return node;
}


tree_node *load_tree(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("No saved tree found. Starting with default.\n");
        return create_node("Is it a Human?");
    }
    
    tree_node *root = load_tree_helper(file);
    fclose(file);
    
    if (root != NULL)
        printf("Tree loaded from %s\n", filename);
    else
        printf("Error loading tree. Starting fresh.\n");
    
    return root;
}