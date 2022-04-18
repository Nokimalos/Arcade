/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** SDLText
*/

#include <stdexcept>
#include <iostream>
#include "SDLText.hpp"

using namespace graphical;

sdl::SDLText::SDLText(const std::string &filePath, SDL_Renderer *renderer) : SDLObject(filePath)
{
    TTF_Init();
    _font = TTF_OpenFont(getInfoFromConfigFile("", "font", filePath).c_str(), 25);
    if (!_font)
        throw AObject::Error("Couldn't load the font.");
    SDL_Color White = _colorMap[_colorsFactory[getInfoFromConfigFile("", "color", filePath)]];
    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(_font, getInfoFromConfigFile("", "graph-txt", filePath).c_str(), White);
    _object = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_QueryTexture(_object, NULL, NULL, &_size.x, &_size.y);
    _pos = (graphical::PosVector_t){std::atoi(getInfoFromConfigFile("", "x", filePath).c_str()), std::atoi(getInfoFromConfigFile("", "y", filePath).c_str())};
    try {
        _scale.x = std::stof(getInfoFromConfigFile("", "sx", filePath));
        _scale.y = std::stof(getInfoFromConfigFile("", "sy", filePath));
    } catch (std::invalid_argument &) {
        _scale.x = 1;
        _scale.y = 1;
    }
    SDL_FreeSurface(surfaceMessage);
}

sdl::SDLText::~SDLText()
{
    TTF_CloseFont(_font);
    TTF_Quit();
    SDL_DestroyTexture(_object);
}