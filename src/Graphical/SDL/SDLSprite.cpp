/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** SDLSprite
*/

#include "SDLSprite.hpp"
#include <SDL_image.h>
#include <stdexcept>

using namespace graphical;

sdl::SDLSprite::SDLSprite(const std::string &filePath, SDL_Renderer *renderer) : SDLObject(filePath)
{
	SDL_Surface *surface = IMG_Load(getInfoFromConfigFile(".graph-2d",
		"path", filePath).c_str());
	if (!surface) {
		throw AObject::Error("Couldn't load the image");
    }
	_object = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(_object, nullptr, nullptr, &_size.x, &_size.y);
    try {
        int sizeX = std::atoi(getInfoFromConfigFile(".graph-2d", "off", filePath).c_str());
        _size.x = (sizeX > 0) ? sizeX : _size.x;
    } catch (std::invalid_argument &) {
    }
    _pos = (graphical::PosVector_t){std::atoi(getInfoFromConfigFile(".graph-2d", "x", filePath).c_str()), std::atoi(getInfoFromConfigFile(".graph-2d", "y", filePath).c_str())};
    _bounds = (FloatRect_t){static_cast<float>(_pos.x),static_cast<float>(_pos.y),
                            static_cast<float>((float)_size.x * _scale.x), static_cast<float>((float)_size.y * _scale.y)};
    try {
        _scale.x = std::stof(getInfoFromConfigFile(".graph-2d", "sx", filePath));
        _scale.y = std::stof(getInfoFromConfigFile(".graph-2d", "sy", filePath));
    } catch (std::invalid_argument &) {
        _scale.x = 1;
        _scale.y = 1;
    }
    SDL_FreeSurface(surface);
}
