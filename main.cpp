#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 572), "Minesweeper");
    Board board(16, 25, 50);
    board.InitializeBoard();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos;
            mousePos = sf::Mouse::getPosition(window);

            unsigned int xPos = mousePos.x/32;
            unsigned int yPos = mousePos.y/32-2;

            if (yPos < 10000) board.FindTile(xPos, yPos).LeftClick();
        }

        window.clear(sf::Color(200, 200, 200));
        board.DrawBoard(window);
        window.display();
    }

    return 0;
}