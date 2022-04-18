/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** NcursesObjects
*/

#include <iostream>
#include <fstream>
#include "NcursesText.hpp"

static std::string getFileContent(const std::string &filePath)
{
    std::ifstream file(filePath);
    std::string line;
    std::string fileContent;

    while (std::getline(file, line))
        fileContent += line + "\n";
    return fileContent;
}

ncurses::NcursesText::NcursesText(const std::string &filePath) : NcursesObject(filePath)
{
    static short currentId = 1;

    _sprite = getFileContent(getInfoFromConfigFile("", "text-txt", filePath));
    if (_sprite.empty())
        _sprite = "?";
    _sprite = _sprite.substr(10);
    _pos = (graphical::PosVector_t){std::atoi(getInfoFromConfigFile("","x", filePath).c_str()), std::atoi(getInfoFromConfigFile("", "y", filePath).c_str())};
    _color = _colorMap[_colorsFactory[getInfoFromConfigFile("", "color", filePath)]];
    _id = currentId++;
    init_pair(_id, _color, COLOR_BLACK);
}