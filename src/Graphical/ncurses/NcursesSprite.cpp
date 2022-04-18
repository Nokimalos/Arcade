/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** NcursesSprite
*/

#include <iostream>
#include <fstream>
#include "NcursesSprite.hpp"

static std::string getFileContent(const std::string &filePath)
{
    std::ifstream file(filePath);
    std::string line;
    std::string fileContent;

    while (std::getline(file, line))
        fileContent += line + "\n";
    return fileContent;
}

ncurses::NcursesSprite::NcursesSprite(const std::string &filePath) : NcursesObject(filePath)
{
    static short currentId = 1;

    _sprite = getInfoFromConfigFile(".text", "char", filePath);
    if (_sprite.empty())
        _sprite = "?";
    _pos = (graphical::PosVector_t){std::atoi(getInfoFromConfigFile(".text","x", filePath).c_str()), std::atoi(getInfoFromConfigFile(".text", "y", filePath).c_str())};
    _color = _colorMap[_colorsFactory[getInfoFromConfigFile(".text", "fg", filePath)]];
    short bgColor = _colorMap[_colorsFactory[getInfoFromConfigFile(".text", "bg", filePath)]];
    _id = currentId++;
    init_pair(_id, _color, bgColor);
}
