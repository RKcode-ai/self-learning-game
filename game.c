#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "game.h"
#include "tree.h"

char get_yes_no(const char *prompt)
{
    char buffer[100];
    char response;
    
    while (1) {
        printf("%s (y/n)\n", prompt);
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
            continue;
        
        response = tolower(buffer[0]);
        
        if (response == 'y' || response == 'n')
            return response;
        
        printf("Please enter 'y' or 'n'\n");
    }
}

char *get_input(const char *prompt)
{
    char buffer[256];
    
    printf("%s\n", prompt);
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        return NULL;
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len-1] == '\n')
        buffer[len-1] = '\0';

    char *result = (char *)malloc(strlen(buffer) + 1);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    strcpy(result, buffer);
    return result;
}

void play_round(tree_node **node_ptr)
{
    tree_node *node = *node_ptr;
    
    if (is_leaf(node)) {
        char answer = get_yes_no(node->text);
        
        if (answer == 'y') {
            printf("I won! I'm so smart!\n");
        } else {
            printf("I give up. What were you thinking about?\n");
            char *correct_answer = get_input("");
            
            printf("Enter a question to distinguish your answer:\n");
            char *new_question = get_input("");
            
            char user_answer = get_yes_no("What is the answer for your object?");

            tree_node *old_guess = create_node(node->text);
            tree_node *new_guess = create_node(correct_answer);
            
            free(node->text);
            node->text = new_question;
            
            if (user_answer == 'y') {
                node->yes = new_guess;
                node->no = old_guess;
            } else {
                node->yes = old_guess;
                node->no = new_guess;
            }
            
            free(correct_answer);
            printf("I've learned something new!\n");
        }
    } else {
        char answer = get_yes_no(node->text);
        
        if (answer == 'y')
            play_round(&(node->yes));
        else
            play_round(&(node->no));
    }
}

void play_game(tree_node **root)
{
    printf("\n=== Guess What Game ===\n");
    printf("Think of something... hit <enter> key when ready...\n");
    getchar();
    
    play_round(root);
    
    printf("\nHit <enter> key to continue...\n");
    getchar();
}