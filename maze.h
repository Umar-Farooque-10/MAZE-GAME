#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <array>

struct Cell {
    bool visited = false;
    std::array<bool, 4> walls = {true, true, true, true};
};

class Maze {
public:
    Maze(int w, int h);
    void generate();
    const Cell &get(int x, int y) const;
    bool isValid(int x, int y) const;
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    void removeWall(Cell &current, Cell &next, int dir);

    int width, height;
    std::vector<std::vector<Cell>> grid;
};

#endif
