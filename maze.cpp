#include "maze.h"
#include <algorithm>
#include <stack>
#include <random>
#include <ctime>

Maze::Maze(int w, int h) : width(w), height(h), grid(w, std::vector<Cell>(h)) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Maze::generate() {
    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y) {
            grid[x][y].visited = false;
            grid[x][y].walls = {true, true, true, true};
        }

    std::stack<std::pair<int, int>> stack;
    int startX = 0, startY = 0;
    grid[startX][startY].visited = true;
    stack.push({startX, startY});

    while (!stack.empty()) {
        auto [x, y] = stack.top();

        std::vector<int> directions = {0, 1, 2, 3};
        std::shuffle(directions.begin(), directions.end(), std::default_random_engine(std::rand()));

        bool found = false;
        for (int dir : directions) {
            int nx = x, ny = y;
            if (dir == 0) ny--;
            else if (dir == 1) nx++;
            else if (dir == 2) ny++;
            else if (dir == 3) nx--;

            if (isValid(nx, ny) && !grid[nx][ny].visited) {
                removeWall(grid[x][y], grid[nx][ny], dir);
                grid[nx][ny].visited = true;
                stack.push({nx, ny});
                found = true;
                break;
            }
        }

        if (!found)
            stack.pop();
    }
}

void Maze::removeWall(Cell &current, Cell &next, int dir) {
    if (dir == 0) {
        current.walls[0] = false;
        next.walls[2] = false;
    } else if (dir == 1) {
        current.walls[1] = false;
        next.walls[3] = false;
    } else if (dir == 2) {
        current.walls[2] = false;
        next.walls[0] = false;
    } else if (dir == 3) {
        current.walls[3] = false;
        next.walls[1] = false;
    }
}

bool Maze::isValid(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

const Cell &Maze::get(int x, int y) const {
    return grid[x][y];
}
