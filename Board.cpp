#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <fstream>
#include "Board.h"
#include "Tile.h"

Board::Board(unsigned int rows, unsigned int cols, unsigned int mines) {
    _rows = rows;
    _cols = cols;
    _mines = mines;

    std::random_device rd;
    std::mt19937 gen(rd());

    for (unsigned int i = 0; i < mines; i++) {
        boolList.push_back(true);
    }
    for (unsigned int i = mines; i < rows*cols; i++) {
        boolList.push_back(false);
    }

    std::shuffle(boolList.begin(), boolList.end(), gen);


    _tiles.resize(_rows); // sets size of the outer vector to amount of rows
    // sets size of the inner vectors to amount of cols
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
    digits.loadFromFile("images/digits.png");
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

    // populates _tiles 2d vector
    for (unsigned int i = 0; i < _rows; i++) {
        for (unsigned int j = 0; j < _cols; j++) {
            Tile newTile;
            newTile.id = counter;

            if (boolList[newTile.id]) newTile._hasMine = true;

            _tiles[i][j] = newTile;
            xPos += 32;
            counter++;
        }
        xPos = 0;
        yPos += 32;
    }

    // populates adjTiles vectors
    for (unsigned int i = 0; i < _rows; i++) {
        for (unsigned int j = 0; j < _cols; j++) {
            if (i == 0) {
                _tiles[i][j].adjTiles.push_back(&_tiles[i+1][j]);
                if (j == 0) {
                    _tiles[i][j].adjTiles.push_back(&_tiles[i][j+1]);
                    _tiles[i][j].adjTiles.push_back(&_tiles[i+1][j+1]);
                    continue;
                }
                if (j == _cols-1) {
                    _tiles[i][j].adjTiles.push_back(&_tiles[i][j-1]);
                    _tiles[i][j].adjTiles.push_back(&_tiles[i+1][j-1]);
                    continue;
                }
                _tiles[i][j].adjTiles.push_back(&_tiles[i][j+1]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i][j-1]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i+1][j+1]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i+1][j-1]);
            }
            else if (i == _rows-1) {
                _tiles[i][j].adjTiles.push_back(&_tiles[i-1][j]);
                if (j == 0) {
                    _tiles[i][j].adjTiles.push_back(&_tiles[i-1][j+1]);
                    _tiles[i][j].adjTiles.push_back(&_tiles[i][j+1]);
                    continue;
                }
                if (j == _cols-1) {
                    _tiles[i][j].adjTiles.push_back(&_tiles[i-1][j-1]);
                    _tiles[i][j].adjTiles.push_back(&_tiles[i][j-1]);
                    continue;
                }
                _tiles[i][j].adjTiles.push_back(&_tiles[i-1][j+1]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i-1][j-1]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i][j-1]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i][j+1]);
            }
            else if (j == 0) {
                if (i == _rows-1) continue;
                _tiles[i][j].adjTiles.push_back(&_tiles[i+1][j]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i+1][j+1]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i][j+1]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i-1][j+1]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i-1][j]);
            }
            else if (j == _cols-1) {
                if (i == _rows-1) continue;
                _tiles[i][j].adjTiles.push_back(&_tiles[i-1][j-1]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i][j-1]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i+1][j-1]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i-1][j]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i+1][j]);
            }
            else {
                _tiles[i][j].adjTiles.push_back(&_tiles[i][j+1]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i][j-1]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i+1][j]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i-1][j]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i+1][j+1]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i-1][j-1]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i+1][j-1]);
                _tiles[i][j].adjTiles.push_back(&_tiles[i-1][j+1]);
            }
        }
    }
}

void Board::InitializeTestBoard(std::string& path) {
    std::ifstream file(path);
    std::vector<bool> inBoolList;
    std::string line;
    unsigned int lineCount = 0;

    while (std::getline(file, line)) {
        for (unsigned int i = 0; i < line.size(); i++) {
            if (line[i] == '1') inBoolList.push_back(true);
            else inBoolList.push_back(false);
        }
        lineCount++;
    }
}

void Board::DrawButtons(sf::RenderWindow &window) {
    int mainDigit = _mines - _flagCounter;

    int digit1 = 0;
    if (mainDigit < 0) digit1 = 10;
    else digit1 = mainDigit / 100;
    sf::Sprite hundredsDigit;
    hundredsDigit.setTexture(digits);
    sf::IntRect rectOne(digit1*21,0,21,32);
    hundredsDigit.setTextureRect(rectOne);
    hundredsDigit.setPosition(16, _rows*32);
    window.draw(hundredsDigit);

    int digit2 = 0;
    if (mainDigit / 10 >= 10) digit2 = mainDigit / 10 % 10;
    else if (mainDigit < 0 && mainDigit / 10 >= 10) digit2 = -mainDigit / 10 % 10;
    else if (mainDigit < 0) digit2 = -mainDigit / 10;
    else digit2 = mainDigit / 10;
    sf::Sprite tensDigit;
    tensDigit.setTexture(digits);
    sf::IntRect rectTwo(digit2*21,0,21,32);
    tensDigit.setTextureRect(rectTwo);
    tensDigit.setPosition(37, _rows*32);
    window.draw(tensDigit);

    int digit3 = 0;
    if (mainDigit < 0) digit3 = -mainDigit % 10;
    else digit3 = mainDigit % 10;
    sf::Sprite onesDigit;
    onesDigit.setTexture(digits);
    sf::IntRect rectThree(digit3*21,0,21,32);
    onesDigit.setTextureRect(rectThree);
    onesDigit.setPosition(58, _rows*32);
    window.draw(onesDigit);

    sf::Sprite faceButton;
    if (_gameStatus == 2) faceButton.setTexture(faceWin);
    else if (_gameStatus == 3) faceButton.setTexture(faceLoss);
    else faceButton.setTexture(face);
    faceButton.setPosition(_cols*32/2-32,_rows*32);
    window.draw(faceButton);

    sf::Sprite debugButton;
    debugButton.setTexture(debugTile);
    debugButton.setPosition(_cols*32-256, _rows*32);
    window.draw(debugButton);

    sf::Sprite testOneButton;
    testOneButton.setTexture(testOneTile);
    testOneButton.setPosition(_cols*32-192, _rows*32);
    window.draw(testOneButton);

    sf::Sprite testTwoButton;
    testTwoButton.setTexture(testTwoTile);
    testTwoButton.setPosition(_cols*32-128, _rows*32);
    window.draw(testTwoButton);

    sf::Sprite testThreeButton;
    testThreeButton.setTexture(testThreeTile);
    testThreeButton.setPosition(_cols*32-64, _rows*32);
    window.draw(testThreeButton);
}

void Board::DrawBoard(sf::RenderWindow &window) {
    // draws tiles, checks for win/loss
    unsigned int counter = 0;
    _flagCounter = 0;
    for (unsigned int i = 0; i < _tiles.size(); i++) {
        for (unsigned int j = 0; j < _tiles[i].size(); j++) {
            // sets _flagCounter
            if (_tiles[i][j]._isFlagged) _flagCounter++;

            // checking for loss
            if (!_tiles[i][j]._isHidden && _tiles[i][j]._hasMine) _gameStatus = 3;

            // add win check with counter here.
            if (!_tiles[i][j]._isHidden) counter++;
            if (_gameStatus == 2) {
                if (_tiles[i][j]._isHidden) _tiles[i][j]._isFlagged = true;
            }

            // drawing based on mine neighbors
            if (_tiles[i][j]._isHidden) {
                _tiles[i][j].DrawTexture(window, hiddenTile, j*32, i*32);
            }
            else if (_tiles[i][j].CheckNeighbors() == 0) {
                _tiles[i][j].DrawTexture(window, revealedTile, j*32, i*32);
            }
            else if (_tiles[i][j].CheckNeighbors() == 1) {
                _tiles[i][j].DrawTexture(window, one, j*32, i*32);
            }
            else if (_tiles[i][j].CheckNeighbors() == 2) {
                _tiles[i][j].DrawTexture(window, two, j*32, i*32);
            }
            else if (_tiles[i][j].CheckNeighbors() == 3) {
                _tiles[i][j].DrawTexture(window, three, j*32, i*32);
            }
            else if (_tiles[i][j].CheckNeighbors() == 4) {
                _tiles[i][j].DrawTexture(window, four, j*32, i*32);
            }
            else if (_tiles[i][j].CheckNeighbors() == 5) {
                _tiles[i][j].DrawTexture(window, five, j*32, i*32);
            }
            else if (_tiles[i][j].CheckNeighbors() == 6) {
                _tiles[i][j].DrawTexture(window, six, j*32, i*32);
            }
            else if (_tiles[i][j].CheckNeighbors() == 7) {
                _tiles[i][j].DrawTexture(window, seven, j*32, i*32);
            }
            else if (_tiles[i][j].CheckNeighbors() == 8) {
                _tiles[i][j].DrawTexture(window, eight, j*32, i*32);
            }

            // drawing flags
            if (_tiles[i][j]._isFlagged) {
                _tiles[i][j].DrawTexture(window, flag, j*32, i*32);
            }

            // draws mines if debug mode is on or loss
            if (_gameStatus == 3 || _gameStatus == 4) {
                if (_tiles[i][j]._hasMine) {
                    _tiles[i][j].DrawTexture(window, mine, j*32, i*32);
                }
            }
        }
    }
    if (counter >= _rows*_cols - _mines && _gameStatus != 3) {
        _gameStatus = 2;
    }
}

void Board::DebugButton() {
    if (_gameStatus == 4) _gameStatus = 1;
    else if (_gameStatus == 1) _gameStatus = 4;
}

unsigned int Board::GetGameStatus() {
    return _gameStatus;
}

Tile& Board::FindTile(unsigned int xPos, unsigned int yPos) {
    // std::cout << yPos << ',';
    // std::cout << xPos << std::endl;
    // std::cout << _tiles[yPos][xPos].id << std::endl;
    // std::cout << _tiles[yPos][xPos].adjTiles.size() << std::endl;
    return _tiles[yPos][xPos];
}