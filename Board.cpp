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

void Board::InitializeBoard() {
    // load textures for tiles
    hiddenTile.loadFromFile("images/tile_hidden.png");
    revealedTile.loadFromFile("images/tile_revealed.png");

    // create game board and tile objects
    unsigned int xPos = 0;
    unsigned int yPos = 64;
    for (unsigned int i = 0; i < _rows; i++) {
        for (unsigned int j = 0; j < _cols; j++) {
            Tile newTile;
            _tiles[i][j] = newTile;
            xPos += 32;
        }
        xPos = 0;
        yPos += 32;
    }
}

void Board::DrawBoard(sf::RenderWindow &window) {
    for (unsigned int i = 0; i < _tiles.size(); i++) {
        for (unsigned int j = 0; j < _tiles[i].size(); j++) {
            _tiles[i][j].DrawTile(window, _tiles[i][j]._isHidden ? hiddenTile : revealedTile, j*32, i*32 + 64);
        }
    }
}

Tile& Board::FindTile(unsigned int xPos, unsigned int yPos) {
    return _tiles[yPos][xPos];
}