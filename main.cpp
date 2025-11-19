#include <SFML/Graphics.hpp>
#include "Board.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 572), "Minesweeper");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(200, 200, 200));
        Board board(16, 25, 50);
        board.InitializeBoard(window);
        window.display();
    }

    return 0;
}