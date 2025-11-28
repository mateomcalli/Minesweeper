#include <SFML/Graphics.hpp>
#include "Tile.h"

void Tile::DrawTexture(sf::RenderWindow &window, sf::Texture &texture, unsigned int xPos, unsigned int yPos) {
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(xPos, yPos);
    window.draw(sprite);
}

unsigned int Tile::CheckNeighbors() {
    unsigned int mineTiles = 0;
    for (unsigned int i = 0; i < adjTiles.size(); i++) {
        if (adjTiles[i]->_hasMine) mineTiles++;
    }
    return mineTiles;
}

void Tile::RecursiveReveal() {
    if (_isFlagged) return;
    _isHidden = false;
    if (CheckNeighbors() != 0) {
        return;
    }
    for (unsigned int i = 0; i < adjTiles.size(); i++) {
        if (!adjTiles[i]->_isHidden) continue;
        if (adjTiles[i]->_isFlagged) continue;

        if (adjTiles[i]->CheckNeighbors() == 0) adjTiles[i]->RecursiveReveal();
        else adjTiles[i]->_isHidden = false;
    }
}

void Tile::LeftClick() {
    if (_isHidden) {
        if (!_hasMine) {
            if (!_isFlagged) {
                RecursiveReveal();
            }
        }
        if (!_isFlagged) _isHidden = false;
    }
}

void Tile::RightClick() {
    if (_isHidden) {
        if (!_isFlagged) {
            _isFlagged = true;
        } else _isFlagged = false;
    }
}