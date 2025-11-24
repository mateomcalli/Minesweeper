#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include "Board.h"
#include "Tile.h"

Board::Board(unsigned int rows, unsigned int cols, unsigned int mines) {
    _rows = rows;
    _cols = cols;
    _mines = mines;
    _mineCounter = mines;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<unsigned int> tempList;

    for (unsigned int i = 1; i < rows*cols + 1; i++) {
        tempList.push_back(i);
    }

    std::shuffle(tempList.begin(), tempList.end(), gen);
    for (unsigned int i = 0; i < mines; i++) {
        _list.push_back(tempList[i]);
    }


    _tiles.resize(_rows);
    for (unsigned int i = 0; i < _rows; i++) {
        _tiles[i].resize(_cols);
    }
}

void Board::LoadTextures() {
    hiddenTile.loadFromFile("images/tile_hidden.png");
    revealedTile.loadFromFile("images/tile_revealed.png");
    face.loadFromFile("images/face_happy.png");
    faceWin.loadFromFile("images/face_win.png");
    faceLoss.loadFromFile("images/face_lose.png");
    debugTile.loadFromFile("images/debug.png");
    flag.loadFromFile("images/flag.png");
    mine.loadFromFile("images/mine.png");
    one.loadFromFile("images/number_1.png");
    two.loadFromFile("images/number_2.png");
    three.loadFromFile("images/number_3.png");
    four.loadFromFile("images/number_4.png");
    five.loadFromFile("images/number_5.png");
    six.loadFromFile("images/number_6.png");
    seven.loadFromFile("images/number_7.png");
    eight.loadFromFile("images/number_8.png");
    testOneTile.loadFromFile("images/test_1.png");
    testTwoTile.loadFromFile("images/test_2.png");
    testThreeTile.loadFromFile("images/test_3.png");
}

void Board::InitializeBoard() {
    LoadTextures();

    // create game board and tile objects
    unsigned int xPos = 0;
    unsigned int yPos = 0;
    unsigned int counter = 0;
    for (unsigned int i = 0; i < _rows; i++) {
        for (unsigned int j = 0; j < _cols; j++) {
            Tile newTile;
            counter++;
            newTile.id = counter;

            auto iter = std::find(_list.begin(), _list.end(), newTile.id);
            if (iter != _list.end()) newTile._hasMine = true;

            _tiles[i][j] = newTile;
            xPos += 32;
        }
        xPos = 0;
        yPos += 32;
    }
}

void Board::DrawBoard(sf::RenderWindow &window) {
    for (unsigned int i = 0; i < _tiles.size(); i++) {
        for (unsigned int j = 0; j < _tiles[i].size(); j++) {
            _tiles[i][j].DrawTexture(window, _tiles[i][j]._isHidden ? hiddenTile : revealedTile, j*32, i*32);
            // if (_tiles[i][j]._hasMine) {
            //     _tiles[i][j].DrawTexture(window, mine, j*32, i*32);
            // }
            if (_tiles[i][j]._isFlagged) {
                _tiles[i][j].DrawTexture(window, flag, j*32, i*32);
            }
        }
    }
}

Tile& Board::FindTile(unsigned int xPos, unsigned int yPos) {
    return _tiles[yPos][xPos];
}