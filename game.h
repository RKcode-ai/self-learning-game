#ifndef GAME_HEADER
#define GAME_HEADER

#include "tree.h"

void play_game(tree_node **root);
char get_yes_no(const char *prompt);
char *get_input(const char *prompt);

#endif