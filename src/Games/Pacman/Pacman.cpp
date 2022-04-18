/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** Pacman
*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <tuple>
#include <map>
#include "Pacman.hpp"

using namespace graphical;

game::Pacman::Pacman()
{
}

game::Pacman::~Pacman()
{

}

extern "C" std::unique_ptr<game::Pacman> getInstance()
{
    return std::make_unique<game::Pacman>();
}

std::vector<std::string> &game::Pacman::getMap()
{
    return _map;
}

std::vector<std::pair<char, std::unique_ptr<graphical::IObject>>> &game::Pacman::getSpritePicker()
{
    return _spritePicker;
}

extern "C" LibType getInstanceType()
{
    return LibType::GAME;
}

static PosVector_t getPacmanStartPos(const std::string &path)
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
                std::replace(line.begin(), line.end(), 'C', '.');
            }
            index++;
        }
    }
    input_file.close();
    if (playerPos.x == -1)
        throw "Invalid starting pos";
    return playerPos;
}

void game::Pacman::loadGameObjects(std::unique_ptr<IGraphical> &graphicalLib)
{
    _score = 0;
    _numberOfPoints = 0;
    _frame = 0;
    _clockForPhantoms.restart();
    _clockToEat.restart();
    _timeToEat = false;
    std::string mapPath = "conf/pacman/pacman-map2.txt";
    PosVector_t startPos = getPacmanStartPos(mapPath);
    std::vector<std::pair<char, std::string>> factory = {
        {'#', "conf/pacman/wall.conf"},
        {'.', "conf/pacman/pacgum.conf"},
        {' ', "conf/empty.conf"},
        {'1', "conf/pacman/portal.conf"},
        {'2', "conf/pacman/portal.conf"},
        {'o', "conf/big-gum.conf"},
        {'M', "conf/pacman/pink-monster.conf"},
        {'P', "conf/pacman/blue-monster.conf"},
        {'Q', "conf/pacman/orange-monster.conf"},
        {'R', "conf/pacman/red-monster.conf"},
        {'3', "conf/pacman/portal.conf"},
        {'4', "conf/pacman/portal.conf"},
        {'5', "conf/pacman/eated_monster_blue.conf"},
        {'6', "conf/pacman/eated_monster_white.conf"},
    };
    createPacmanMap(mapPath);
    createPhantomVector();
    for (auto &element : factory) {
        _spritePicker.emplace_back(element.first, graphicalLib->createObject(element.second));
    }
    _pacman = {
        graphicalLib->createObject("conf/pacman/pacman-up.conf"),
        graphicalLib->createObject("conf/pacman/pacman-right.conf"),
        graphicalLib->createObject("conf/pacman/pacman-down.conf"),
        graphicalLib->createObject("conf/pacman/pacman-left.conf"),
    };
    for (auto &pac : _pacman) {
        pac->setPos(startPos);
    }
    factory.clear();
}

game::GameState game::Pacman::run(std::unique_ptr<IGraphical> &graphicalLib, game::event::Events &event)
{
    static Directions toDraw = RIGHT;
    _frame++;
    static std::map<Directions, std::tuple<int, int, game::event::KeyCode>> playerPos = {
        {UP, {0, -1, game::event::keyZ}},
        {RIGHT, {1, 0, game::event::keyD}},
        {DOWN, {0, 1, game::event::keyS}},
        {LEFT, {-1, 0, game::event::keyQ}},
    };
    if (event.key.code == event::Unknown) {
        event.type = game::event::KeyPressed;
        event.key.code = std::get<2>(playerPos[toDraw]);
    }
    if (event.type == game::event::KeyPressed) {
        game::event::KeyCode key = event.key.code;
        for (auto &pos : playerPos) {
            if (std::get<2>(pos.second) == key) {
                toDraw = pos.first;
                if (std::get<2>(pos.second) == key && canMove(pos.first, toDraw, playerPos))
                    move(pos.first, playerPos);
                break;
            }
        }
    }
    graphicalLib->windowClear();
    displayMap(getMap(), graphicalLib, getSpritePicker());
    displayPhantoms(graphicalLib);
    checkTeleporter();
    if (eatPoints() == true) {
        reloadGame();
        loadGameObjects(graphicalLib);
    }
    eatBubbleGum();
    eatPhantoms();
    movePhantoms();
    endTimeToEat();
    graphicalLib->drawObject(_pacman[toDraw]);
    graphicalLib->windowDisplay();
    return Running;
}

void game::Pacman::setGraphicalLib(IGraphical &graphicalLib)
{
    for (auto &sprite : _spritePicker) {
        graphicalLib.reloadSprite(sprite.second);
    }
    for (auto &i : _pacman) {
        graphicalLib.reloadSprite(i);
    }
}

void game::Pacman::reloadGame()
{
    _map.clear();
    _score = 0;
    _numberOfPoints = 0;
    _frame = 0;
    _spritePicker.clear();
    _charMap.clear();
    _phantom.clear();
    _clockToEat.restart();
    _clockForPhantoms.restart();
}
