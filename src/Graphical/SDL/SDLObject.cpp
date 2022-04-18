/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** SDLObject
*/

#include <stdexcept>
#include <iostream>
#include "SDLObject.hpp"

using namespace graphical;

sdl::SDLObject::SDLObject(const std::string &filePath) : AObject(filePath)
{
    _object = nullptr;
    _pos = (PosVector_t){};
    _scale = (FloatVector_t){};
    _size = (PosVector_t){};
    _bounds = (FloatRect_t){static_cast<float>(_pos.x * 40),static_cast<float>(_pos.y * 40),static_cast<float>((float)_size.x * _scale.x), static_cast<float>((float)_size.y * _scale.y)};
}

sdl::SDLObject::~SDLObject()
{
	SDL_DestroyTexture(_object);
}

void sdl::SDLObject::movPos(int offsetX, int offsetY)
{
	_pos = {_pos.x + offsetX, _pos.y + offsetY};
}

void sdl::SDLObject::setPos(const PosVector_t &pos)
{
	_pos = {pos.x, pos.y};
}

void sdl::SDLObject::setPos(int newX, int newY)
{
	_pos = {newX, newY};
}

graphical::PosVector_t &sdl::SDLObject::getPos()
{
	return _pos;
}

const graphical::PosVector_t &sdl::SDLObject::getSize()
{
    return _size;
}

const graphical::FloatVector_t &sdl::SDLObject::getScale()
{
    return _scale;
}

const FloatRect_t &sdl::SDLObject::getBounds()
{
    _bounds = (FloatRect_t){static_cast<float>(_pos.x * 40),static_cast<float>(_pos.y * 40),static_cast<float>((float)_size.x * _scale.x), static_cast<float>((float)_size.y * _scale.y)};
    return _bounds;
}

SDL_Texture *sdl::SDLObject::getObject()
{
    return _object;
}