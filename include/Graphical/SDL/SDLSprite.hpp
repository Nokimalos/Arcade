/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** SDLSprite
*/

#ifndef SPRITESDL_HPP_
    #define SPRITESDL_HPP_

#include "SDLObject.hpp"

using namespace graphical;

namespace sdl {
    class SDLSprite : public SDLObject {
    public:
        SDLSprite(const std::string &filePath, SDL_Renderer *renderer);
    };
}

#endif /* !SPRITESDL_HPP_ */
