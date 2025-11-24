#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"

void Tile::DrawTexture(sf::RenderWindow &window, sf::Texture &texture, unsigned int xPos, unsigned int yPos) {
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(xPos, yPos);
    window.draw(sprite);
}

void Tile::LeftClick() {
    if (_isHidden) {
        if (!_hasMine) {
            if (!_isFlagged) {
                _isHidden = false;
            }
        }
    }
}

void Tile::RightClick() {
    if (_isHidden) {
        if (!_isFlagged) {
            _isFlagged = true;
        } else _isFlagged = false;
    }
}