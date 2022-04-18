/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** Nibbler
*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <tuple>
#include <map>
#include "Nibbler.hpp"

using namespace graphical;

game::Nibbler::Nibbler() : _score(0)
{

}

game::Nibbler::~Nibbler()
{
}

extern "C" std::unique_ptr<game::Nibbler> getInstance()
{
    return std::make_unique<game::Nibbler>();
}

std::vector<std::string> &game::Nibbler::getMap()
{
    return _map;
}

std::vector<std::pair<char, std::unique_ptr<graphical::IObject>>> &game::Nibbler::getSpritePicker()
{
    return _spritePicker;
}

extern "C" LibType getInstanceType()
{
    return LibType::GAME;
}

std::array<std::unique_ptr<graphical::IObject>, 4> &game::Nibbler::getNibbler()
{
    return _nibbler;
}

void game::Nibbler::createNibblerMap(const std::string &path)
{
    std::ifstream input_file(path);
    std::string line;

    if (!input_file.is_open()) {
        throw "Could not open map file";
    } else {
        while (std::getline(input_file, line)) {
            if (line.find('C') != std::string::npos) {
                std::replace(line.begin(), line.end(), 'C', ' ');
            }
            _map.push_back(line);
        }
    }
    input_file.close();
}

void game::Nibbler::displayBody(std::unique_ptr<graphical::IGraphical> &lib)
{
    for (auto &part : _body) {
        if (part.first == 0)
            continue;
        _spritePicker[_charMap['N']].second->setPos(part.second.x, part.second.y);
        lib->drawObject(_spritePicker[_charMap['N']].second);
    }
}

static PosVector_t getNibblerStartPos(const std::string &path)
{
    std::ifstream input_file(path);
    std::string line;
    PosVector_t playerPos = {-1, -1};
    int index = 0;

    if (!input_file.is_open()) {
        throw "Could not open map file";
    } else {
        while (std::getline(input_file, line)) {
            if (line.find("C") != std::string::npos) {
                playerPos = {int(line.find('C')), index};
            }
            index++;
        }
    }
    input_file.close();
    if (playerPos.x == -1)
        throw "Invalid starting pos";
    return playerPos;
}

std::string resizeString(const std::string &string, const int &size = 2)
{
    std::string resized;

    for (auto character : string) {
        for (int i = 0; i < size; i++) {
            resized.push_back(character);
        }
    }
    return resized;
}

void game::Nibbler::reloadGame()
{
    _body.clear();
    _charMap.clear();
    _map.clear();
    _score = 0;
    _spritePicker.clear();
    _toDraw = RIGHT;
}

void game::Nibbler::loadGameObjects(std::unique_ptr<IGraphical> &graphicalLib)
{
    _toDraw = RIGHT;
    std::string mapPath = "conf/nibbler/nibbler-map2.txt";
    PosVector_t startPos = getNibblerStartPos(mapPath);
    std::vector<std::pair<char, std::string>> factory = {
        {'#', "conf/nibbler/wall3.conf"},
        {' ', "conf/empty.conf"},
        {'*', "conf/nibbler/nibbler-food.conf"},
        {'N', "conf/nibbler/nibbler-body.conf"},
    };

    _charMap = {
        {'#', 0},
        {' ', 1},
        {'*', 2},
        {'N', 3},
    };

    createNibblerMap(mapPath);
    for (auto &element : factory) {
        _spritePicker.emplace_back(element.first, graphicalLib->createObject(element.second));
    }
    _nibbler = {
        graphicalLib->createObject("conf/nibbler/nibbler-up.conf"),
        graphicalLib->createObject("conf/nibbler/nibbler-right.conf"),
        graphicalLib->createObject("conf/nibbler/nibbler-down.conf"),
        graphicalLib->createObject("conf/nibbler/nibbler-left.conf"),
    };
    for (auto &pac : _nibbler) {
        pac->setPos(startPos);
    }
    for (int i = 0; i < 4; i++) {
        _body.push_back({i, {startPos.x - i, startPos.y}});
    }
    factory.clear();
}

void game::Nibbler::setGraphicalLib(IGraphical &graphicalLib)
{
    for (auto &sprite : _spritePicker) {
        graphicalLib.reloadSprite(sprite.second);
    }
    for (auto &i : _nibbler) {
        graphicalLib.reloadSprite(i);
    }
}
