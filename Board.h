#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Board {
    unsigned int _rows;
    unsigned int _cols;
    unsigned int _mines;
    unsigned int _mineCounter;
    std::vector<std::vector<Tile>> _tiles;

    // textures
    sf::Texture hiddenTile;
    sf::Texture revealedTile;
    sf::Texture face;
    sf::Texture faceWin;
    sf::Texture faceLoss;
    sf::Texture debugTile;
    sf::Texture testOneTile;
    sf::Texture testTwoTile;
    sf::Texture testThreeTile;
    sf::Texture flag;
    sf::Texture mine;
    sf::Texture one;
    sf::Texture two;
    sf::Texture three;
    sf::Texture four;
    sf::Texture five;
    sf::Texture six;
    sf::Texture seven;
    sf::Texture eight;

public:
    Board(unsigned int rows, unsigned int cols, unsigned int mines);
    void LoadTextures();
    void InitializeBoard(); // makes 2D vector with tiles
    void DrawTexture(sf::RenderWindow &window, sf::Texture &texture, unsigned int xPos, unsigned int yPos);
    void DrawBoard(sf::RenderWindow &window); // draws tiles to screen, runs constantly
    Tile& FindTile(unsigned int xPos, unsigned int yPos);
};