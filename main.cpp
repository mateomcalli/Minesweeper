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

            // calls LeftClick() function
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePos;
                mousePos = sf::Mouse::getPosition(window);

                unsigned int xPos = mousePos.x/32;
                unsigned int yPos = mousePos.y/32;

                // handles clicks outside of tiles
                if (xPos >= cols || yPos >= rows) {
                    if (mousePos.y <= rows*32+64) {
                        // face button
                        if (cols*32/2-32 <= mousePos.x && mousePos.x <= cols*32/2+32) {
                            board = Board(rows,cols,mines);
                            board.InitializeBoard();
                        }

                        // debug button
                        if (cols*32-256 <= mousePos.x && mousePos.x < cols*32-192) {
                            board.DebugButton();
                        }

                        // test 1-3 buttons
                        if (cols*32-192 <= mousePos.x && mousePos.x < cols*32-128) {
                            board = Board(rows,cols,mines);
                            std::string board1 = "boards/testboard1.brd";
                            board.InitializeTestBoard(board1);
                        }
                        if (cols*32-128 <= mousePos.x && mousePos.x < cols*32-64) {
                            board = Board(rows,cols,mines);
                            std::string board2 = "boards/testboard2.brd";
                            board.InitializeTestBoard(board2);
                        }
                        if (cols*32-64 <= mousePos.x && mousePos.x <= cols*32) {
                            board = Board(rows,cols,mines);
                            std::string board3 = "boards/testboard3.brd";
                            board.InitializeTestBoard(board3);
                        }
                    }
                }

                // handles other clicks (tiles)
                else {
                    if (board.GetGameStatus() == 1 || board.GetGameStatus() == 4) {
                        board.FindTile(xPos, yPos).LeftClick();
                    }
                }
            }

            // calls RightClick() function
            else if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Right)
            {
                sf::Vector2i mousePos;
                mousePos = sf::Mouse::getPosition(window);

                unsigned int xPos = mousePos.x/32;
                unsigned int yPos = mousePos.y/32;

                // ignores clicks outside of game area
                if (xPos >= cols || yPos >= rows) {
                    continue;
                }

                // handles right clicks in game area
                else {
                    if (board.GetGameStatus() == 1 || board.GetGameStatus() == 4) {
                        board.FindTile(xPos, yPos).RightClick();
                    }
                }
            }
        }

        window.clear(sf::Color(200, 200, 200));
        board.DrawButtons(window);
        board.DrawBoard(window);
        window.display();
    }

    return 0;
}