#include "solvers.h"
#include <stack>
#include <queue>
#include <unordered_map>
#include <algorithm>

std::vector<std::pair<int, int>> solveMazeDFS(const Maze& maze, int startX, int startY, int endX, int endY) {
    std::vector<std::pair<int, int>> path;
    std::stack<std::pair<int, int>> stack;
    std::unordered_map<int, std::unordered_map<int, bool>> visited;
    std::unordered_map<int, std::unordered_map<int, std::pair<int, int>>> parent;

    stack.push({startX, startY});
    visited[startX][startY] = true;

    while (!stack.empty()) {
        auto [x, y] = stack.top();
        stack.pop();

        if (x == endX && y == endY) {
            while (!(x == startX && y == startY)) {
                path.push_back({x, y});
                auto [px, py] = parent[x][y];
                x = px;
                y = py;
            }
            path.push_back({startX, startY});
            std::reverse(path.begin(), path.end());
            return path;
        }

        if (!maze.get(x, y).walls[0] && !visited[x][y - 1]) {
            visited[x][y - 1] = true;
            parent[x][y - 1] = {x, y};
            stack.push({x, y - 1});
        }
        if (!maze.get(x, y).walls[1] && !visited[x + 1][y]) {
            visited[x + 1][y] = true;
            parent[x + 1][y] = {x, y};
            stack.push({x + 1, y});
        }
        if (!maze.get(x, y).walls[2] && !visited[x][y + 1]) {
            visited[x][y + 1] = true;
            parent[x][y + 1] = {x, y};
            stack.push({x, y + 1});
        }
        if (!maze.get(x, y).walls[3] && !visited[x - 1][y]) {
            visited[x - 1][y] = true;
            parent[x - 1][y] = {x, y};
            stack.push({x - 1, y});
        }
    }

    return path;
}

std::vector<std::pair<int, int>> solveMazeBFS(const Maze& maze, int startX, int startY, int endX, int endY) {
    std::vector<std::pair<int, int>> path;
    std::queue<std::pair<int, int>> queue;
    std::unordered_map<int, std::unordered_map<int, bool>> visited;
    std::unordered_map<int, std::unordered_map<int, std::pair<int, int>>> parent;

    queue.push({startX, startY});
    visited[startX][startY] = true;

    while (!queue.empty()) {
        auto [x, y] = queue.front();
        queue.pop();

        if (x == endX && y == endY) {
            while (!(x == startX && y == startY)) {
                path.push_back({x, y});
                auto [px, py] = parent[x][y];
                x = px;
                y = py;
            }
            path.push_back({startX, startY});
            std::reverse(path.begin(), path.end());
            return path;
        }

        if (!maze.get(x, y).walls[0] && !visited[x][y - 1]) {
            visited[x][y - 1] = true;
            parent[x][y - 1] = {x, y};
            queue.push({x, y - 1});
        }
        if (!maze.get(x, y).walls[1] && !visited[x + 1][y]) {
            visited[x + 1][y] = true;
            parent[x + 1][y] = {x, y};
            queue.push({x + 1, y});
        }
        if (!maze.get(x, y).walls[2] && !visited[x][y + 1]) {
            visited[x][y + 1] = true;
            parent[x][y + 1] = {x, y};
            queue.push({x, y + 1});
        }
        if (!maze.get(x, y).walls[3] && !visited[x - 1][y]) {
            visited[x - 1][y] = true;
            parent[x - 1][y] = {x, y};
            queue.push({x - 1, y});
        }
    }

    return path;
}
