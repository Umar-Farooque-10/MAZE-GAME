#include <SFML/Graphics.hpp>
#include "maze.h"
#include "solvers.h"
#include <windows.h>
#include <chrono>
#include <iostream>
#include <vector>
#include <sstream>

int main() {
    const int CELL_SIZE = 20;
    const int WALL_THICKNESS = 4;
    const int WIDTH = 40, HEIGHT = 30;
    Maze maze(WIDTH, HEIGHT);
    maze.generate();

    sf::RenderWindow window(sf::VideoMode(WIDTH * CELL_SIZE, HEIGHT * CELL_SIZE + 100), "Maze Game");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // Handle error
    }

    int playerX = 0, playerY = 0;
    bool gameWon = false;
    std::vector<std::pair<int, int>> path;

    std::string dfsTimeText = "DFS Time: Not calculated";
    std::string bfsTimeText = "BFS Time: Not calculated";

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                int newX = playerX, newY = playerY;
                if (!gameWon) {
                    if (event.key.code == sf::Keyboard::Up && !maze.get(playerX, playerY).walls[0])
                        newY--;
                    else if (event.key.code == sf::Keyboard::Right && !maze.get(playerX, playerY).walls[1])
                        newX++;
                    else if (event.key.code == sf::Keyboard::Down && !maze.get(playerX, playerY).walls[2])
                        newY++;
                    else if (event.key.code == sf::Keyboard::Left && !maze.get(playerX, playerY).walls[3])
                        newX--;
                }

                if (maze.isValid(newX, newY)) {
                    playerX = newX;
                    playerY = newY;
                }

                if (event.key.code == sf::Keyboard::R) {
                    maze.generate();
                    playerX = 0;
                    playerY = 0;
                    gameWon = false;
                    path.clear();
                    dfsTimeText = "DFS Time: Not calculated";
                    bfsTimeText = "BFS Time: Not calculated";
                }

                // Solve maze using different algorithms
                if (event.key.code == sf::Keyboard::D) {
                    auto start = std::chrono::high_resolution_clock::now();
                    path = solveMazeDFS(maze, 0, 0, WIDTH - 1, HEIGHT - 1);
                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                    std::ostringstream oss;
                    oss << "DFS Time: " << duration.count() << " milliseconds";
                    dfsTimeText = oss.str();
                    std::cout << dfsTimeText << std::endl;
                }
                if (event.key.code == sf::Keyboard::B) {
                    auto start = std::chrono::high_resolution_clock::now();
                    path = solveMazeBFS(maze, 0, 0, WIDTH - 1, HEIGHT - 1);
                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                    std::ostringstream oss;
                    oss << "BFS Time: " << duration.count() << " milliseconds";
                    bfsTimeText = oss.str();
                    std::cout << bfsTimeText << std::endl;
                }
            }
        }

        if (playerX == WIDTH - 1 && playerY == HEIGHT - 1 && !gameWon) {
            gameWon = true;
            MessageBoxA(NULL, "You reached the goal!", "Success", MB_OK | MB_ICONINFORMATION);
        }

        window.clear(sf::Color::White);

        sf::RectangleShape wall;
        wall.setFillColor(sf::Color::Black);

        for (int x = 0; x < WIDTH; ++x) {
            for (int y = 0; y < HEIGHT; ++y) {
                float x1 = x * CELL_SIZE;
                float y1 = y * CELL_SIZE;
                float x2 = x1 + CELL_SIZE;
                float y2 = y1 + CELL_SIZE;

                const Cell &cell = maze.get(x, y);
                if (cell.walls[0]) {
                    wall.setSize(sf::Vector2f(CELL_SIZE, WALL_THICKNESS));
                    wall.setPosition(x1, y1);
                    window.draw(wall);
                }
                if (cell.walls[1]) {
                    wall.setSize(sf::Vector2f(WALL_THICKNESS, CELL_SIZE));
                    wall.setPosition(x2 - WALL_THICKNESS, y1);
                    window.draw(wall);
                }
                if (cell.walls[2]) {
                    wall.setSize(sf::Vector2f(CELL_SIZE, WALL_THICKNESS));
                    wall.setPosition(x1, y2 - WALL_THICKNESS);
                    window.draw(wall);
                }
                if (cell.walls[3]) {
                    wall.setSize(sf::Vector2f(WALL_THICKNESS, CELL_SIZE));
                    wall.setPosition(x1, y1);
                    window.draw(wall);
                }
            }
        }

        // Draw the path
        sf::RectangleShape pathCell(sf::Vector2f(CELL_SIZE / 2, CELL_SIZE / 2));
        pathCell.setFillColor(sf::Color::Blue);
        for (const auto &cell : path) {
            pathCell.setPosition(cell.first * CELL_SIZE + CELL_SIZE / 4, cell.second * CELL_SIZE + CELL_SIZE / 4);
            window.draw(pathCell);
        }

        // Start
        sf::CircleShape start(CELL_SIZE / 4);
        start.setFillColor(sf::Color::Green);
        start.setOutlineColor(sf::Color::White);
        start.setOutlineThickness(2);
        start.setPosition(CELL_SIZE / 4, CELL_SIZE / 4);
        window.draw(start);

        // End
        sf::CircleShape end(CELL_SIZE / 4);
        end.setFillColor(sf::Color::Red);
        end.setOutlineColor(sf::Color::White);
        end.setOutlineThickness(2);
        end.setPosition((WIDTH - 1) * CELL_SIZE + CELL_SIZE / 4, (HEIGHT - 1) * CELL_SIZE + CELL_SIZE / 4);
        window.draw(end);

        // Player
        sf::RectangleShape player(sf::Vector2f(CELL_SIZE / 2, CELL_SIZE / 2));
        player.setFillColor(sf::Color::Yellow);
        player.setOutlineColor(sf::Color::Black);
        player.setOutlineThickness(2);
        player.setPosition(playerX * CELL_SIZE + CELL_SIZE / 4, playerY * CELL_SIZE + CELL_SIZE / 4);
        window.draw(player);

        
        // Display time taken for each algorithm
        sf::Text dfsText(dfsTimeText, font, 20);
        dfsText.setFillColor(sf::Color::Black);
        dfsText.setPosition(10, HEIGHT * CELL_SIZE + 10);
        window.draw(dfsText);

        sf::Text bfsText(bfsTimeText, font, 20);
        bfsText.setFillColor(sf::Color::Black);
        bfsText.setPosition(10, HEIGHT * CELL_SIZE + 40);
        window.draw(bfsText);

        window.display();
    }

    return 0;
}