/*
** EPITECH PROJECT, 2022
** B-OOP-400-PAR-4-1-arcade-kaan.bouldoires
** File description:
** SDLRectangleShape
*/

#ifndef RECTNAGLESHAPESDL_HPP_
#define RECTNAGLESHAPESDL_HPP_

#include "SDLObject.hpp"

using namespace graphical;

namespace sdl {
    class SDLRectangleShape : public SDLObject {
    public:
        SDLRectangleShape(const std::string &filePath, SDL_Renderer *renderer);
    };

}

#endif /* !RECTNAGLESHAPESDL_HPP_ */
