#ifndef SOLVERS_H
#define SOLVERS_H

#include "maze.h"
#include <vector>
#include <utility>

std::vector<std::pair<int, int>> solveMazeDFS(const Maze& maze, int startX, int startY, int endX, int endY);
std::vector<std::pair<int, int>> solveMazeBFS(const Maze& maze, int startX, int startY, int endX, int endY);

#endif
