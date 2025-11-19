#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Tile.h"
#include <vector>

Board::Board(unsigned int rows, unsigned int cols, unsigned int mines) {
    _rows = rows;
    _cols = cols;
    _mines = mines;
    _mineCounter = mines;

    _tiles.resize(_rows);
    for (unsigned int i = 0; i < _rows; i++) {
        _tiles[i].resize(_cols);
    }
}

void Board::InitializeBoard(sf::RenderWindow &window) {
    unsigned int xPos = 0;
    unsigned int yPos = 64;
    for (unsigned int i = 0; i < _rows; i++) {
        for (unsigned int j = 0; j < _cols; j++) {
            Tile newTile;
            newTile.DrawTile(window, xPos, yPos);
            _tiles[i][j] = newTile;
            xPos += 32;
        }
        xPos = 0;
        yPos += 32;
    }
}

