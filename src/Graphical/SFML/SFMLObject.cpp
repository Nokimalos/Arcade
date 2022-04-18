/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** SFMLObjects
*/

#include "SFMLObject.hpp"

sfml::SFMLObject::SFMLObject(const std::string &filePath) : AObject(filePath)
{
    _pos = (graphical::PosVector_t){std::atoi(getInfoFromConfigFile(".graph-2d","x", filePath).c_str()), std::atoi(getInfoFromConfigFile(".graph-2d", "y", filePath).c_str())};
}

void sfml::SFMLObject::movPos(int offsetX, int offsetY)
{
    _pos = {_pos.x + offsetX, _pos.y + offsetY};
}

void sfml::SFMLObject::setPos(const PosVector_t &pos)
{
    _pos = {pos.x, pos.y};
}

void sfml::SFMLObject::setPos(int newX, int newY)
{
    _pos = {newX, newY};
}

graphical::PosVector_t &sfml::SFMLObject::getPos()
{
    return _pos;
}