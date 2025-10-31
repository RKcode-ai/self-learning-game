#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "game.h"
#include "io.h"

#define SAVE_FILE "Questions_Answers.txt"

int main()
{
    tree_node *root = NULL;
    root = load_tree(SAVE_FILE);
    
    if (root == NULL) {
        root = create_node("Is it a Human?");
    }
    
    char play_again;
    do {
        play_game(&root);
        
        play_again = get_yes_no("Play again?");
        
    } while (play_again == 'y');
    
    save_tree(root, SAVE_FILE);
    
    free_tree(root);
    
    printf("Thanks for playing! Goodbye.\n");
    
    return 0;
}