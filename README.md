# Maze Game

Maze Game is a C++ project that generates and displays a random maze using SFML for graphics. The player can navigate the maze, and the game includes options to solve the maze using DFS or BFS algorithms, displaying the time taken for each.

## Main Files

### `main.cpp`
- Entry point of the application.
- Handles window creation, event processing, rendering, and user interaction.
- Allows the player to move through the maze, regenerate it, and visualize solutions using DFS or BFS.
- Displays timing information for each solving algorithm.

### `maze.cpp`
- Implements the `Maze` class methods.
- Contains the maze generation algorithm using randomized DFS (backtracking).
- Handles wall removal between cells and maze validation logic.

### `maze.h`
- Declares the `Cell` struct and `Maze` class.
- Defines the maze's data structures, public interface, and utility methods for maze manipulation and querying.

---

## How to Play

- Use arrow keys to move the player through the maze.
- Press `R` to regenerate a new maze.
- Press `D` to solve the maze using DFS and display the time taken.
- Press `B` to solve the maze using BFS and display the time taken.
- Reach the red circle (goal) to win!

## Requirements

- C++ compiler
- [SFML](https://www.sfml-dev.org/) library
- `arial.ttf` font file in the executable directory
"# MAZE-GAME" 
