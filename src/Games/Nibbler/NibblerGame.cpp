
/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** NibblerGame
*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <tuple>
#include <map>
#include <ctime>
#include "Nibbler.hpp"

using namespace graphical;

void game::Nibbler::displayMap(std::unique_ptr<IGraphical> &graphicalLib)
{
    for (int y = 0; y < _map.size(); y++) {
        for (int x = 0; x < _map[y].size(); x++) {
            _spritePicker[_charMap[_map[y][x]]].second->setPos(x, y);
            graphicalLib->drawObject(_spritePicker[_charMap[_map[y][x]]].second);
        }
    }
}

bool isObstacle(char tile)
{
    std::vector<char> obstacles = {
        '#',
        'N',
    };

    for (auto &c : obstacles) {
        if (tile == c) {
            return true;
        }
    }
    return false;
}

void game::Nibbler::moveBody()
{
    static int count = 0;
    int size = _body.size();

    for (int i = size - 1; i > 0; i--) {
        _body[i].second.x = _body[i - 1].second.x;
        _body[i].second.y = _body[i - 1].second.y;
    }
}

static bool isFoodInMap(const char &food, const std::vector<std::string> &map)
{
    for (auto &line : map) {
        for (auto &c : line) {
            if (c == food) {
                return true;
            }
        }
    }
    return false;
}

void game::Nibbler::addFood(int &frameCounter)
{
    int mapWidth = _map[0].length();
    int mapHeight = _map.size();
    int randLine = std::rand() % mapHeight;
    int randCol = std::rand() % mapWidth;
    PosVector_t randPos = {randLine, randCol};

    if (frameCounter == 40)
        frameCounter = 0;
    else if (!isFoodInMap('*', getMap())) {}
    else
        return;
    while (isObstacle(_map[randPos.x][randPos.y]) || _nibbler[0]->getPos() == randPos ||
        _map[randPos.x][randPos.y] == '*') {
        randPos = {std::rand() % mapHeight, std::rand() % mapWidth};
    }
    _map[randPos.x][randPos.y] = '*';

}

void game::Nibbler::die()
{
    PosVector_t headPos = _nibbler[0]->getPos();
    int bodyIndex = 0;

    for (auto &bodyPart : _body) {
        if (headPos == bodyPart.second && bodyIndex != 0) {
            std::cout << "Nibbler: game over" << std::endl;
            exit(0);
        }
        bodyIndex++;
    }
}

void game::Nibbler::eatFood()
{
    PosVector_t headPos = _nibbler[0]->getPos();
    PosVector_t tailPos = {_body[_body.size() - 1].second.x,
        _body[_body.size() - 1].second.y};
    static int numberEaten = 0;

    if (_map[headPos.y][headPos.x] == '*') {
        _map[headPos.y][headPos.x] = ' ';
        _body.push_back({_body.size(), {-1, -1}});
        _score += 42;
    }
}

std::vector<std::pair<int, graphical::PosVector_t>> &game::Nibbler::getBody()
{
    return _body;
}

bool game::Nibbler::canMove(const Directions &direction, const Directions &oldDirection,
    std::map<Directions, std::tuple<int, int, game::event::KeyCode>> &playerPos)
{
    PosVector_t pos = _nibbler[0]->getPos();
    int offsetX = std::get<0>(playerPos[direction]);
    int offsetY = std::get<1>(playerPos[direction]);

    if (direction != (oldDirection + 2) % 4 && !isObstacle(getMap()[pos.y + offsetY][pos.x + offsetX]))
        return true;
    else
        return false;
}

Directions game::Nibbler::move(const Directions &direction,
    std::map<Directions, std::tuple<int, int, game::event::KeyCode>> &playerPos)
{
    PosVector_t pos = _nibbler[0]->getPos();
    for (auto &nibbler : _nibbler) {
        int offsetX = std::get<0>(playerPos[direction]);
        int offsetY = std::get<1>(playerPos[direction]);
        nibbler->movPos(offsetX, offsetY);
        getBody()[0].second.x = nibbler->getPos().x;
        getBody()[0].second.y = nibbler->getPos().y;
    }
    return direction;
}

game::GameState game::Nibbler::run(std::unique_ptr<IGraphical> &graphicalLib, game::event::Events &event)
{
    static int frameCounter = 0;
    frameCounter++;
    addFood(frameCounter);
    static std::map<Directions, std::tuple<int, int, game::event::KeyCode>> playerPos = {
        {UP, {0, -1, game::event::keyZ}},
        {RIGHT, {1, 0, game::event::keyD}},
        {DOWN, {0, 1, game::event::keyS}},
        {LEFT, {-1, 0, game::event::keyQ}},
    };

    if (event.key.code == event::Unknown) {
        event.type = game::event::KeyPressed;
        event.key.code = std::get<2>(playerPos[_toDraw]);
    }
    if (event.type == game::event::KeyPressed) {
        game::event::KeyCode key = event.key.code;
        for (auto &pos : playerPos) {
            if (std::get<2>(pos.second) == key && canMove(pos.first, _toDraw, playerPos)) {
                moveBody();
                _toDraw = move(pos.first, playerPos);
                break;
            }
        }
    }
    graphicalLib->windowClear();
    displayMap(graphicalLib);
    displayBody(graphicalLib);
    die();
    eatFood();
    graphicalLib->drawObject(_nibbler[_toDraw]);
    graphicalLib->windowDisplay();
    return Running;
}
