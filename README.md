# Candy Crush-Inspired Game

## Overview

This project is a simplified version of the popular game Candy Crush, implemented in C++. The game involves matching candies of the same color to score points and collect stars. The game offers two modes: a timed mode and a move-based mode. The player can swap adjacent candies to create matches of three or more, and the game provides hints if the player is stuck.

## Features

- **Two Game Modes**:
  - **Timer Mode**: The player has a limited time to make as many matches as possible.
  - **Move Mode**: The player has a limited number of moves to achieve the goal of collecting stars.

- **Dynamic Grid Initialization**: The game grid is dynamically initialized with random candy colors, ensuring no initial matches.

- **Match Detection**: The game automatically detects and removes matches of three or more candies of the same color.

- **Star Collection**: The game includes stars that can be collected by matching candies in their vicinity.

- **Hints**: If the player is stuck, the game provides hints on possible moves.

- **Interactive Menu**: The game features an interactive menu for starting the game, viewing instructions, and exiting.

## How to Play

1. **Start the Game**: Choose the "Start" option from the main menu.
2. **Select Mode**: Choose between Timer Mode or Move Mode.
3. **Swap Candies**: Enter the coordinates of the two candies you want to swap. The candies must be adjacent.
4. **Create Matches**: Swap candies to create matches of three or more of the same color to score points and collect stars.
5. **Use Hints**: If you're stuck, the game will provide hints after a certain period of inactivity.
6. **Win the Game**: Collect all stars to win the game.

## Code Structure

The project is organized into several files:

- **`linkedlistmatrix.h` and `linkedlistmatrix.cpp`**: These files define a 2D linked list structure used to represent the game grid. The `Matrix` class represents a node in the grid, and the `LinkedList2D` class manages the grid.

- **`candyCrash.h` and `candyCrash.cpp`**: These files contain the main game logic. The `Node` class represents a candy in the grid, and the `Grid` class manages the game state, including grid initialization, match detection, and user interaction.

- **`candyCrashMain.cpp`**: This file contains the `main` function, which handles the game loop and user input.

## Compilation and Execution

To compile and run the game, use the following commands:

```bash
g++ -o candyCrash candyCrashMain.cpp candyCrash.cpp linkedlistmatrix.cpp
./candyCrash
```

## Dependencies

- **C++ Standard Library**: The game uses standard C++ libraries for input/output, threading, and random number generation.
- **Multi-threading**: The game uses threads to manage the countdown timer and hint system.

## Future Improvements

- **Enhanced Graphics**: Implement a graphical user interface (GUI) for a more engaging user experience.
- **More Levels**: Add multiple levels with increasing difficulty.
- **Power-ups**: Introduce power-ups that can be used to clear large sections of the grid.

## License

This project is open-source and available under the MIT License. Feel free to modify and distribute it as per the license terms.

## Author

This project was developed as a part of a programming exercise. Contributions and feedback are welcome!
