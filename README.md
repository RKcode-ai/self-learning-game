# Self Learning Game

A classic "20 Questions" style guessing game implemented in C that learns from its mistakes. The game uses a binary decision tree to store questions and answers, expanding its knowledge base with each incorrect guess.

## Overview

Think of something, and the game will try to guess it by asking yes/no questions. If it guesses wrong, it asks you to teach it a new question to distinguish your answer from its guess. Over time, the game becomes smarter and builds a comprehensive knowledge tree that persists between sessions.

## Features

- **Interactive Gameplay**: Binary search through yes/no questions
- **Self-Learning**: Automatically expands its knowledge when it guesses incorrectly
- **Persistent Storage**: Saves the decision tree to a file for continuous learning
- **Memory Safe**: Proper dynamic memory management with cleanup

## How It Works

The game maintains a binary tree structure where:
- **Internal nodes** contain questions
- **Leaf nodes** contain guesses
- **Yes/No answers** determine which branch to follow

When the game makes an incorrect guess, it:
1. Asks what you were thinking of
2. Requests a question to distinguish your answer from its guess
3. Updates the tree by converting the leaf into a question node with two new guesses

## Project Structure

```
.
├── main.c          # Entry point and game loop
├── game.c/h        # Game logic and user interaction
├── tree.c/h        # Binary tree data structure
├── io.c/h          # File I/O for saving/loading the tree
└── Questions_Answers.txt  # Saved knowledge base (generated)
```

## Compilation

```bash
gcc -o game main.c game.c tree.c io.c -Wall
```

Or using a Makefile:

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = game
OBJS = main.o game.o tree.o io.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)
```

## Usage

1. Run the game:
   ```bash
   ./game
   ```

2. Think of something (an animal, object, person, etc.)

3. Answer the questions with 'y' (yes) or 'n' (no)

4. If the game guesses correctly, it wins! If not, teach it a new question

5. Play again or quit - your progress is automatically saved

## Example Session

```
=== Guess What Game ===
Think of something... hit <enter> key when ready...

Is it a Human? (y/n)
n
I give up. What were you thinking about?
Dog
Enter a question to distinguish your answer:
Does it have four legs?
What is the answer for your object? (y/n)
y
I've learned something new!

Play again? (y/n)
```

## File Format

The knowledge tree is saved in a simple text format:
- `Q` = Question node
- `G` = Guess (leaf) node
- `#` = Null node
- Each node's text follows on the next line

Example:
```
Q
Is it a Human?
G
Person
Q
Does it have four legs?
G
Dog
G
Snake
```

## Technical Details

- **Language**: C (C99 standard)
- **Data Structure**: Binary decision tree
- **Memory Management**: Dynamic allocation with proper cleanup
- **Input Handling**: Robust user input validation
- **File I/O**: Recursive tree serialization/deserialization

## Functions

### Tree Operations (`tree.c`)
- `create_node()` - Allocate and initialize a tree node
- `free_tree()` - Recursively free all tree memory
- `is_leaf()` - Check if a node is a leaf

### Game Logic (`game.c`)
- `play_game()` - Main game loop
- `play_round()` - Recursive question/answer traversal
- `get_yes_no()` - Get validated yes/no input
- `get_input()` - Get string input from user

### I/O Operations (`io.c`)
- `save_tree()` - Persist tree to file
- `load_tree()` - Load tree from file

## Memory Management

The program properly manages memory by:
- Allocating nodes and strings dynamically
- Freeing all allocated memory before exit
- Handling allocation failures gracefully

## Future Enhancements

- [ ] Add ability to browse the knowledge tree
- [ ] Implement undo/redo functionality
- [ ] Support multiple save files
- [ ] Add statistics (win rate, total games played)
- [ ] Implement tree balancing for better performance
- [ ] Add export to DOT format for visualization

## License

This project is open source and available for educational purposes.

## Contributing

Contributions are welcome! Feel free to submit issues or pull requests.

---

**Note**: On first run, if no save file exists, the game starts with a simple default question: "Is it a Human?"
