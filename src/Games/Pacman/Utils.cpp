/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** Utils
*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <tuple>
#include <map>
#include "Pacman.hpp"

using namespace graphical;

bool game::Pacman::isObstacle(char tile)
{
    std::vector<char> obstacles = {
        '#',
        'C',
    };
    for (auto &ch : obstacles)
        if (tile == ch)
            return true;
    return false;
}

bool game::Pacman::isTeleporter(char tile)
{
    std::vector<char> point = {
        '1',
        '2',
        '3',
        '4',
    };
    for (auto &ch : point)
        if (tile == ch)
            return true;
    return false;
}

bool game::Pacman::canMove(const Directions &direction, const Directions &oldDirection,
    std::map<Directions, std::tuple<int, int, game::event::KeyCode>> &playerPos)
{
    PosVector_t pos = _pacman[0]->getPos();
    int offsetX = std::get<0>(playerPos[direction]);
    int offsetY = std::get<1>(playerPos[direction]);

    if (!isObstacle(getMap()[pos.y + offsetY][pos.x + offsetX]))
        return true;
    else
        return false;
}

Directions game::Pacman::move(const Directions &dir,
    std::map<Directions, std::tuple<int, int, game::event::KeyCode>> &playerPos)
{
    PosVector_t pos = _pacman[0]->getPos();

    for (auto &pac : _pacman) {
        int offsetX = std::get<0>(playerPos[dir]);
        int offsetY = std::get<1>(playerPos[dir]);
        pac->movPos(offsetX, offsetY);
    }
    return dir;
}

void game::Pacman::displayPhantoms(std::unique_ptr<IGraphical> &lib)
{
    for (auto &ph : _phantom) {
        _spritePicker[_charMap[ph.first]].second->setPos(ph.second);
        if (_timeToEat == true) {
            _spritePicker[12].second->setPos(ph.second);
            lib->drawObject(_spritePicker[12].second);
        } else {
            lib->drawObject(_spritePicker[_charMap[ph.first]].second);
        }
    }
}

void game::Pacman::createPhantomVector()
{
    for (int line = 0; line < _map.size(); line++) {
        for (int col = 0; col < _map[line].length(); col++) {
            if (_map[line][col] == 'M' || _map[line][col] == 'P'
            || _map[line][col] == 'Q' || _map[line][col] == 'R') {
                _phantom.insert({_map[line][col], {col, line}});
                _map[line][col] = ' ';
            }
        }
    }
}

std::vector<PosVector_t>
    game::Pacman::getFreePositionAround(PosVector_t &phantomPos) const
{
    std::vector<PosVector_t> freePos;
    std::vector<PosVector_t> aroundPosition = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0},
    };
    for (PosVector_t &i : aroundPosition) {
        char car = _map[(phantomPos + i).y][(phantomPos + i).x];
        if (_map[(phantomPos + i).y][(phantomPos + i).x] == '.' ||
            _map[(phantomPos + i).y][(phantomPos + i).x] == ' ') {
            freePos.push_back(phantomPos + i);
        }
    }
    return freePos;
}

void game::Pacman::movePhantoms()
{
    std::vector<PosVector_t> freePos;
    PosVector_t getGoodPhantom;
    char phantomChar;

    if ((_timeToEat && _frame == 30) || (_frame >= 10 && !_timeToEat)) {
        _frame = 0;
        if (_clockForPhantoms.getElapsedTime() > 10000) {
            for (auto &phantomIte : _phantom) {
                phantomChar = _map[phantomIte.second.y][phantomIte.second.x];
                freePos = getFreePositionAround(phantomIte.second);
                getGoodPhantom = freePos[std::rand() % freePos.size()];
                phantomIte.second = getGoodPhantom;
                freePos.clear();
            }
        }
    }
}