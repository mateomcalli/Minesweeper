#pragma once
#include <SFML/Graphics.hpp>

struct Tile {
    bool _isHidden = true;
    bool _isFlagged = false;
    bool _hasMine = false;
    bool _hasFlag = false;
public:
    void LeftClick(); // unhide, lose game if tile has mine
    void RightClick(); // add/remove flag
    void DrawTile(sf::RenderWindow &window, sf::Texture &texture, unsigned int xPos, unsigned int yPos);
};