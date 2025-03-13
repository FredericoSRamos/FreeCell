# Freecell Game (CLI version) - C Implementation

This is a command-line implementation of the Freecell card game written in C. It uses stacks to manage the game state and simulates the Freecell rules, where the goal is to move all cards to the foundation piles in ascending order (from Ace to King) for each suit.

## How to Play

- The game consists of 8 game columns (main piles), 4 foundation piles (to stack cards by suit), and 4 free cells (to temporarily hold cards).
- The objective is to stack all the cards from Ace to King of the same suit in the foundation piles.
- The game columns can hold cards in alternating colors, and each card in a column must be one value lower than the one below it.
- Free cells can hold only one card at a time and can be used to help move cards around.

## Gameplay

1. You start with 8 piles of cards dealt randomly, and you can interact with the game by:
   - Moving a card from one pile to another by specifying the pile number you wish to take from and the pile number you want to place the card in.
   - You can move a card to the foundation piles (columns 13-16) or a free cell (columns 9-12).
   - Cards can only be moved according to Freecell's rules (e.g., you can move a red 7 on top of a black 8, but not vice versa).
   
2. The game continues until all cards are in the foundation piles (you win) or if no valid moves are left (you lose).

### Column Mapping

- Columns 1-8: Game columns (main piles).
- Columns 9-12: Free cells (you can hold a card in each free cell).
- Columns 13-16: Foundation piles (for each suit, you stack the cards in ascending order).

## Requirements

- C compiler (e.g., GCC)
- Standard C libraries: `stdio.h`, `stdlib.h`, `time.h`

## How to Compile and Run

1. Clone or download the repository.
2. Open a terminal and navigate to the directory containing the source code.
3. Compile the program using a C compiler (e.g., GCC):

   ```bash
   gcc -o freecell freecell.c
