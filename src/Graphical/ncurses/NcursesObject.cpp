/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** NcursesObjects
*/

#include <iostream>
#include <fstream>
#include "NcursesObject.hpp"

ncurses::NcursesObject::NcursesObject(const std::string &filePath) : AObject(filePath)
{
    _bounds = (FloatRect_t){};
}

short &ncurses::NcursesObject::getId()
{
    return _id;
}

const std::string &ncurses::NcursesObject::getObject()
{
	return _sprite;
}

void ncurses::NcursesObject::movPos(int offsetX, int offsetY)
{
	_pos = {_pos.x + offsetX, _pos.y + offsetY};
}

void ncurses::NcursesObject::setPos(const PosVector_t &pos)
{
	_pos = pos;
}

void ncurses::NcursesObject::setPos(int newX, int newY)
{
	_pos = {newX, newY};
}

graphical::PosVector_t &ncurses::NcursesObject::getPos()
{
	return _pos;
}

const FloatRect_t &ncurses::NcursesObject::getBounds()
{
    return _bounds;
}