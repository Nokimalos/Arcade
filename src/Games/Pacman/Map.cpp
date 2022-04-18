/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** Map
*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <tuple>
#include <map>
#include <list>
#include "Pacman.hpp"

using namespace graphical;

const int MAX_POINT = 222;

void game::Pacman::createPacmanMap(const std::string &path)
{
    std::ifstream input_file(path);
    std::string line;

    if (!input_file.is_open()) {
        throw "Could not open map file";
    } else {
        while (std::getline(input_file, line)) {
            if (line.find("C") != std::string::npos) {
                std::replace(line.begin(), line.end(), 'C', '.');
            }
            _map.push_back(line);
        }
    }
    input_file.close();
}

void game::Pacman::displayMap(std::vector<std::string> &map, std::unique_ptr<IGraphical> &graphicalLib,
                std::vector<std::pair<char, std::unique_ptr<IObject>>> &spritePicker)
{
    std::list<char> phantomChars = {'M', 'P', 'Q', 'R'};

    _charMap = {
        {'#', 0},
        {'.', 1},
        {' ', 2},
        {'1', 3},
        {'2', 3},
        {'o', 5},
        {'M', 6},
        {'P', 7},
        {'Q', 8},
        {'R', 9},
        {'3', 3},
        {'4', 3},
        {'5', 12},
        {'6', 11},
    };
    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[y].size() - 1; x++) {
            spritePicker[_charMap[map[y][x]]].second->setPos(x, y);
            graphicalLib->drawObject(spritePicker[_charMap[map[y][x]]].second);
        }
    }
}

void game::Pacman::teleportPacman(int tpLine, int tpCol)
{
    PosVector_t pacmanPos = _pacman[0]->getPos();
    char teleporter = _map[tpLine][tpCol];

    std::map<char, int> teleporterMap = {
        {'1', 0},
        {'2', 1},
        {'3', 2},
        {'4', 3},
    };

    for (int i = 0; i < _map.size(); i++) {
        for (int j = 0; j < _map[i].length(); j++) {
            if (teleporterMap.find(_map[i][j]) != teleporterMap.end()
                && teleporterMap[_map[i][j]] ==
                ((teleporterMap[teleporter] + 2) % teleporterMap.size())
                && (i != tpLine || j != tpCol)) {
                for (auto &pos : _pacman) {
                    if (teleporterMap[_map[i][j]] == 0)
                        pos->setPos(j + 1, i);
                    if (teleporterMap[_map[i][j]] == 1)
                        pos->setPos(j + 1, i);
                    if (teleporterMap[_map[i][j]] == 2)
                        pos->setPos(j - 1, i);
                    if (teleporterMap[_map[i][j]] == 3)
                        pos->setPos(j - 1, i);
                }
                return;
            } 
        }
    }
}

void game::Pacman::checkTeleporter()
{
    PosVector_t pacmanPos = _pacman[0]->getPos();

    if (isTeleporter(_map[pacmanPos.y][pacmanPos.x]))
        teleportPacman(pacmanPos.y, pacmanPos.x);
}

bool game::Pacman::eatPoints()
{
    PosVector_t pacmanPos = _pacman[0]->getPos();

    if (_map[pacmanPos.y][pacmanPos.x] == '.') {
        _score++;
        _numberOfPoints++;
        _map[pacmanPos.y][pacmanPos.x] = ' ';
    }
    if (_numberOfPoints >= MAX_POINT) {
        std::cout << "Nice ! Your score for this level is " << _score << "!" << std::endl;
        return true;
    }
    return false;
}

void game::Pacman::eatBubbleGum()
{
    PosVector_t pacmanPos = _pacman[0]->getPos();

    if (_map[pacmanPos.y][pacmanPos.x] == 'o') {
        _map[pacmanPos.y][pacmanPos.x] = ' ';
        _timeToEat = true;
        _clockToEat.restart();
    }
}

void game::Pacman::endTimeToEat()
{
    if (_timeToEat && _clockToEat.getElapsedTime() > 10000) {
        _clockToEat.restart();
        _timeToEat = false;
    }
}

void game::Pacman::eatPhantoms()
{
    PosVector_t pacmanPos = _pacman[0]->getPos();

    for (auto &phantom : _phantom) {
        if (pacmanPos == phantom.second && !_timeToEat) {
            std::cout << "Your final score is " << _score << std::endl;
            exit(0);
        }
        if (pacmanPos == phantom.second && _timeToEat) {
            _score += 100;
            _phantom.erase(phantom.first);
        }
    }
}