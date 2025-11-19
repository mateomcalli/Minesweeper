#include <SFML/Graphics.hpp>
#include "Tile.h"

void Tile::DrawTile(sf::RenderWindow &window, sf::Texture &texture, unsigned int xPos, unsigned int yPos) {
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(xPos, yPos);
    window.draw(sprite);
}

void Tile::LeftClick() {
    if (_isHidden) {
        if (!_hasMine) {
            _isHidden = false;
        }
    }
}
