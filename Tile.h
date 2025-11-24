#pragma once
#include <SFML/Graphics.hpp>

struct Tile {
    unsigned int id;
    bool _isHidden = true;
    bool _isFlagged = false;
    bool _hasMine = false;
public:
    void LeftClick(); // unhide, lose game if tile has mine
    void RightClick(); // add/remove flag
    void DrawTexture(sf::RenderWindow &window, sf::Texture &texture, unsigned int xPos, unsigned int yPos);
};