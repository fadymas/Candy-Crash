# Candy Crush-Inspired Game

## Overview

This project is a simplified version of the Candy Crush game implemented in C++ using linked lists. The game is played on a 30x30 grid where each cell (node) represents a candy. The main objective is to collect all the stars on the grid by making valid moves that align three or more candies of the same color.

## Features

- _30x30 Grid:_ The game board is represented using a 30x30 grid of linked list nodes.
- _Two-Stage Initialization:_ The grid is initialized in two stages - first by placing stars and then by assigning candy colors.
- _Move Validation:_ Players can only make moves that result in a match of 3 or more candies of the same color.
- _Match Detection:_ Detects and removes matches, collects stars, and refills the grid with new candies.
- _Game Objective:_ Collect all 5 stars within a user-defined move limit or timer to win the game.

- _Dynamic Move Limit and Timer:_ You can modify the move limit and timer (default 50 seconds) dynamically through the configuration before the game starts.
- _Command Line Display:_ The game is displayed in the command line with clear indicators for stars and candies.

## File Structure

- `candycrush.h `: Defines the node structure and function prototypes for grid manipulation and game logic.
- `candycrush.cpp `: Implements the functions for creating the grid, swapping nodes, match detection, and reinitialization of colors.
- candycrushmain.cpp: Contains the main game loop, user interaction, and the timer feature.
- linkedlistmatrix.h: Defines the matrix structure for linked list nodes, including pointer references to neighboring nodes.
- linkedlistmatrix.cpp: Implements the linked list logic for grid manipulation, including the adjacency of nodes and updating candy colors.

## How to Compile

To compile the game, use the following command in the terminal:

```sh
g++ candycrushmain.cpp candycrush.cpp linkedlistmatrix.cpp -o CandyCrushGame
```
