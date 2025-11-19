#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Board {
    unsigned int _rows;
    unsigned int _cols;
    unsigned int _mines;
    unsigned int _mineCounter;
    std::vector<std::vector<Tile>> _tiles;
public:
    Board(unsigned int rows, unsigned int cols, unsigned int mines);
    void InitializeBoard(sf::RenderWindow &window);
};