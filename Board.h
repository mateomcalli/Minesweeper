#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Board {
    unsigned int _rows;
    unsigned int _cols;
    unsigned int _mines;
    unsigned int _mineCounter;
    sf::Texture hiddenTile;
    sf::Texture revealedTile;
    std::vector<std::vector<Tile>> _tiles;
public:
    Board(unsigned int rows, unsigned int cols, unsigned int mines);
    void InitializeBoard(); // makes 2D vector with tiles, loads textures
    void DrawBoard(sf::RenderWindow &window); // draws tiles to screen, runs constantly
    Tile& FindTile(unsigned int xPos, unsigned int yPos);
};