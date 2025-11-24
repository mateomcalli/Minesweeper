#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Board.h"

int main() {
    std::ifstream config("boards/config.cfg");
    unsigned int cols, rows, mines;

    if (config.is_open()) {
        config >> cols;
        config >> rows;
        config >> mines;
    }

    sf::RenderWindow window(sf::VideoMode(cols*32, rows*32+100), "Minesweeper");
    Board board(rows, cols, mines);
    board.InitializeBoard();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePos;
                mousePos = sf::Mouse::getPosition(window);

                unsigned int xPos = mousePos.x/32;
                unsigned int yPos = mousePos.y/32;

                if (xPos >= cols || yPos >= rows) {
                    continue;
                } else board.FindTile(xPos, yPos).LeftClick();
            }

            else if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Right)
            {
                sf::Vector2i mousePos;
                mousePos = sf::Mouse::getPosition(window);

                unsigned int xPos = mousePos.x/32;
                unsigned int yPos = mousePos.y/32;

                if (xPos >= cols || yPos >= rows) {
                    continue;
                } else board.FindTile(xPos, yPos).RightClick();
            }
        }

        window.clear(sf::Color(200, 200, 200));
        board.DrawBoard(window);
        window.display();
    }

    return 0;
}