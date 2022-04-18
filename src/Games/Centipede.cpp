/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** Centipede
*/

#include <iostream>
#include <functional>
#include <tuple>
#include <map>
#include "Centipede.hpp"

using namespace graphical;

game::Centipede::Centipede()
{

}

game::Centipede::~Centipede()
{
}

extern "C" std::unique_ptr<game::Centipede> getInstance()
{
    return std::make_unique<game::Centipede>();
}

extern "C" LibType getInstanceType()
{
    return LibType::GAME;
}

std::vector<std::string> &game::Centipede::getMap()
{
    return _map;
}

std::vector<std::pair<char, std::unique_ptr<graphical::IObject>>> &game::Centipede::getSpritePicker()
{
    return _spritePicker;
}

std::string createRandomLine()
{
    std::string line;

    for (int i = 0; i < 49; ++i)
        line += (rand() % 40 == 0 && i != 0 && i != MAX_X_WINDOW - 1) ? '4' : ' ';
    return line;
}

void game::Centipede::createCentipedeMap(const std::string &path)
{
    srand(time(nullptr));
    for (int i = 0; i < 25; ++i)
        _map.emplace_back(createRandomLine());
}

static PosVector_t getPlayerStartPos(const std::string &path)
{
    PosVector_t playerPos = {0, 20};

    srand(time(nullptr));
    playerPos.x = rand() % 50;
    playerPos.y += rand() % 5;
    return playerPos;
}

std::vector<std::pair<std::array<std::unique_ptr<graphical::IObject>, 3>, Directions>> game::Centipede::createCentipede(std::unique_ptr<graphical::IGraphical> &graphicalLib, int length)
{
    std::vector<std::pair<std::array<std::unique_ptr<graphical::IObject>, 3>, Directions>> centipede;
    for (int i = 0; i < length; ++i) {
        if (i == 0)
            centipede.emplace_back((std::pair<std::array<std::unique_ptr<graphical::IObject>, 3>, Directions>){
                    (std::array<std::unique_ptr<graphical::IObject>, 3>){
                            graphicalLib->createObject("conf/centipede/centipede-head-right.conf"),
                            graphicalLib->createObject("conf/centipede/centipede-head-down.conf"),
                            graphicalLib->createObject("conf/centipede/centipede-head-left.conf"),
                    }, DOWN});
        else
            centipede.emplace_back((std::pair<std::array<std::unique_ptr<graphical::IObject>, 3>, Directions>){
                    (std::array<std::unique_ptr<graphical::IObject>, 3>){
                            graphicalLib->createObject("conf/centipede/centipede-body-right.conf"),
                            graphicalLib->createObject("conf/centipede/centipede-body-down.conf"),
                            graphicalLib->createObject("conf/centipede/centipede-body-left.conf"),
                    }, DOWN});
    }
    for (auto &centipedePart : centipede) {
        for (auto &centipedePartDir: centipedePart.first)
            centipedePartDir->setPos(15, 0);
    }
    return centipede;
}

void game::Centipede::loadGameObjects(std::unique_ptr<IGraphical> &graphicalLib)
{
    int lifePosX = 0;
    std::string mapPath = "conf/pacman/pacman-map2.txt";
    PosVector_t startPlayerPos = getPlayerStartPos(mapPath);
    std::vector<std::pair<char, std::string>> factory = {
        {'4', "conf/centipede/mushroom-full.conf"},
        {'3', "conf/centipede/mushroom-3-4.conf"},
        {'2', "conf/centipede/mushroom-half.conf"},
        {'1', "conf/centipede/mushroom-1-4.conf"},
        {' ', "conf/empty.conf"},
        {'F', "conf/centipede/fire.conf"},
    };

    createCentipedeMap(mapPath);
    _lastCentipedeDir = LEFT;
    for (auto &element : factory) {
        _spritePicker.emplace_back(element.first, graphicalLib->createObject(element.second));
    }
    _player = graphicalLib->createObject("conf/centipede/player.conf");
    _player->setPos(startPlayerPos);
    for (int i = 0; i < 3; ++i)
        _life.emplace_back(graphicalLib->createObject("conf/centipede/player.conf"));
    for (auto &life : _life) {
        life->setPos(lifePosX, 0);
        lifePosX += 1;
    }
    _centipede.emplace_back(createCentipede(graphicalLib, 12));
    factory.clear();
}

void displayMap(std::vector<std::string> &map, std::unique_ptr<IGraphical> &graphicalLib,
                std::vector<std::pair<char, std::unique_ptr<IObject>>> &spritePicker)
{
    std::map<char, int> charMap = {
        {'4', 0},
        {'3', 1},
        {'2', 2},
        {'1', 3},
        {' ', 4},
        {'F', 5},
    };

    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[y].size() - 1; x++) {
            spritePicker[charMap[map[y][x]]].second->setPos(x, y);
            graphicalLib->drawObject(spritePicker[charMap[map[y][x]]].second);
        }
    }
    charMap.clear();
}

bool game::Centipede::caseEmpty(int offsetX, int offsetY, PosVector_t pos)
{
    if (_map[pos.y + offsetY][pos.x + offsetX] == ' ' || _map[pos.y + offsetY][pos.x + offsetX] == 'F')
        return true;
    return false;
}

bool game::Centipede::moveCentipede(const std::function<bool(std::unique_ptr<graphical::IObject>&, Directions, bool)> &move)
{
    bool goDown = false;

    for (auto &centipede : _centipede) {
        bool head = true;
        PosVector_t oldPos = {};
        Directions oldDir;
        for (auto &centipedePart: centipede) {
            if (head) {
                oldPos = centipedePart.first[0]->getPos();
                oldDir = centipedePart.second;
                head = false;
                for (auto &centipedePartDir: centipedePart.first) {
                    if (centipedePartDir->getPos().y == MAX_Y_WINDOW) {
                        return false;
                    }
                    if (!move(centipedePartDir, centipedePart.second, (centipedePartDir->getPos().y >= MIN_Y_WINDOW) && (centipedePartDir->getPos().x < MAX_X_WINDOW || (centipedePartDir->getPos().x == MAX_X_WINDOW && centipedePart.second != RIGHT)) && (centipedePartDir->getPos().x > MIN_X_WINDOW || (centipedePartDir->getPos().x == MIN_X_WINDOW && centipedePart.second != LEFT)))) {
                        _lastCentipedeDir = centipedePart.second;
                        goDown = true;
                    }
                }
                if (centipedePart.second == DOWN && !goDown) {
                    centipedePart.second = (_lastCentipedeDir == RIGHT) ? LEFT : RIGHT;
                }
                if (goDown) {
                    centipedePart.second = DOWN;
                    goDown = false;
                }
            } else {
                PosVector_t tmpPos = oldPos;
                oldPos = centipedePart.first[0]->getPos();
                Directions tmpDir = oldDir;
                oldDir = centipedePart.second;
                for (auto &centipedePartDir: centipedePart.first) {
                    centipedePartDir->setPos(tmpPos);
                    centipedePart.second = tmpDir;
                }
            }
        }
    }
    return true;
}

void game::Centipede::moveFire()
{
    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].length(); j++) {
            if (_map[i][j] == 'F' && i > 0) {
                _map[i][j] = ' ';
                if (_map[i - 1][j] > '1' && _map[i - 1][j] <= '4')
                    _map[i - 1][j] -= 1;
                else if (_map[i - 1][j] == '1')
                    _map[i - 1][j] = ' ';
                else
                    _map[i - 1][j] = 'F';
            } else if (_map[i][j] == 'F' && i == 0)
                _map[i][j] = ' ';
        }
    }
}

std::vector<std::pair<std::array<std::unique_ptr<graphical::IObject>, 3>, Directions>> splitCentipede(std::vector<std::pair<std::array<std::unique_ptr<graphical::IObject>, 3>, Directions>> &centipede, int posToSplit)
{
    std::vector<std::pair<std::array<std::unique_ptr<graphical::IObject>, 3>, Directions>> newCentipede;

    for (int i = 0; i + posToSplit < centipede.size(); i++) {
        newCentipede.emplace_back((std::pair<std::array<std::unique_ptr<graphical::IObject>, 3>, Directions>){std::move(centipede[i + posToSplit].first), ((centipede[i + posToSplit].second == RIGHT) ? LEFT : RIGHT)});
    }
    if (posToSplit == 0 || posToSplit == 1)
        centipede.clear();
    else
        centipede.resize(posToSplit);
    return newCentipede;
}

bool game::Centipede::collideWithCentipede(std::unique_ptr<graphical::IGraphical> &graphicalLib)
{
    int posInCentipedeVec = 0;
    for (auto &centipede : _centipede) {
        int posInCentipede = 0;
        for (auto &centipedePart : centipede) {
            PosVector_t centipedePartPos = centipedePart.first[0]->getPos();
            if (centipedePartPos == _player->getPos())
                return true;
            if (_map[centipedePartPos.y][centipedePartPos.x] == 'F') {
                _map[centipedePartPos.y][centipedePartPos.x] = '4';
                _centipede.emplace_back(splitCentipede(centipede, posInCentipede));
                if (posInCentipede == 0 || posInCentipede == 1)
                    _centipede.erase(_centipede.begin()+posInCentipedeVec);
                return false;
            }
            ++posInCentipede;
        }
        ++posInCentipedeVec;
    }
    return false;
}

game::GameState game::Centipede::run(std::unique_ptr<IGraphical> &graphicalLib, game::event::Events &event)
{
    static Directions toDraw = RIGHT;
    static std::map<Directions, std::tuple<int, int, game::event::KeyCode>> playerPos = {
        {RIGHT, {1, 0, game::event::keyD}},
        {DOWN, {0, 1, game::event::keyS}},
        {LEFT, {-1, 0, game::event::keyQ}},
        {UP, {0, -1, game::event::keyZ}},
    };
    static std::function<bool(std::unique_ptr<graphical::IObject>&, Directions, bool)> move = [&](std::unique_ptr<graphical::IObject> &object, Directions draw, bool condition) {
        if ((object->getPos().x == 0 && std::get<0>(playerPos[draw]) == -1) ||
        (object->getPos().x == MAX_X_WINDOW && std::get<0>(playerPos[draw]) == 1) ||
                (object->getPos().y == MAX_Y_WINDOW && std::get<1>(playerPos[draw]) == 1))
            return false;
        if (caseEmpty(std::get<0>(playerPos[draw]), std::get<1>(playerPos[draw]), object->getPos()) && condition) {
            object->movPos(std::get<0>(playerPos[draw]), std::get<1>(playerPos[draw]));
            return true;
        }
        return false;
    };
    if (event.type == game::event::KeyPressed) {
        if (event.key.code == game::event::keySpace) {
            _map[_player->getPos().y][_player->getPos().x] = 'F';
        }
        game::event::KeyCode key = event.key.code;
        for (auto &test : playerPos)
            if (std::get<2>(test.second) == key) {
                toDraw = test.first;
                move(_player, toDraw, ((_player->getPos().y > MIN_Y_PLAYER || (_player->getPos().y == MIN_Y_PLAYER && toDraw != UP)) && (_player->getPos().y < MAX_Y_WINDOW || (_player->getPos().y == MAX_Y_WINDOW && toDraw != DOWN)) && (_player->getPos().x < MAX_X_WINDOW || (_player->getPos().x == MAX_X_WINDOW && toDraw != RIGHT)) && (_player->getPos().x > MIN_X_WINDOW || (_player->getPos().x == MIN_X_WINDOW && toDraw != LEFT))));
                break;
            }
    }
    graphicalLib->windowClear();
    displayMap(getMap(), graphicalLib, getSpritePicker());
    if (!moveCentipede(move) || collideWithCentipede(graphicalLib)) {
        _life.erase(_life.begin());
        if (_life.empty())
            return Lose;
        _centipede.clear();
        _centipede.emplace_back(createCentipede(graphicalLib, 12));
        return Running;
    }
    for (auto &centipede : _centipede) {
        for (auto &centipedePart: centipede) {
            graphicalLib->drawObject(centipedePart.first[centipedePart.second]);
        }
    }
    for (auto &life : _life)
        graphicalLib->drawObject(life);
    graphicalLib->drawObject(_player);
    moveFire();
    graphicalLib->windowDisplay();
    return Running;
}

void game::Centipede::setGraphicalLib(IGraphical &graphicalLib)
{
    for (auto &sprite : _spritePicker) {
        graphicalLib.reloadSprite(sprite.second);
    }
    for (auto &centipede : _centipede)
        for (auto &centipedePart : centipede)
            for (auto &centipedePartDir : centipedePart.first)
                graphicalLib.reloadSprite(centipedePartDir);
    for (auto &life : _life)
        graphicalLib.reloadSprite(life);
    graphicalLib.reloadSprite(_player);
}

void game::Centipede::reloadGame()
{
    _centipede.clear();
    _life.clear();
    _map.clear();
    _player.release();
    _score = 0;
    _spritePicker.clear();
    _lastCentipedeDir = DOWN;
}