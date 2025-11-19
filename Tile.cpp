#include <SFML/Graphics.hpp>
#include "Tile.h"

void Tile::DrawTile(sf::RenderWindow &window, unsigned int xPos, unsigned int yPos) {
    sf::Texture tileImg;
    tileImg.loadFromFile("images/tile_hidden.png");

    sf::Sprite sprite;
    sprite.setTexture(tileImg);
    sprite.setPosition(xPos, yPos);
    window.draw(sprite);
}
