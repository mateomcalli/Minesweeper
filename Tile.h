#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct Tile {
    unsigned int id;
    bool _isHidden = true;
    bool _isFlagged = false;
    bool _hasMine = false;
    std::vector<Tile*> adjTiles;
public:
    void LeftClick(); // unhide, lose game if tile has mine
    void RightClick(); // add/remove flag
    unsigned int CheckNeighbors(); // returns number that should go on revealed tile
    void RecursiveReveal();
    void DrawTexture(sf::RenderWindow &window, sf::Texture &texture, unsigned int xPos, unsigned int yPos);
};